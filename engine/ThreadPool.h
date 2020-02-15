#ifndef THREADPOOL_H
#define THREADPOOL_H
#include <thread>
#include <queue>
#include <vector>
#include <functional>
//#include <Event.h>

#include <Event.h>
#include <MarketData.h>
#include <TradeMessage.h>
#include "Worker.h"


namespace engine
{

class ThreadPool
{
friend class Worker;
private:
    using Workers = std::vector<Worker::Ptr>;

    int _numThreads;
    std::shared_ptr<std::queue<Task>> _task_queue = std::make_shared<std::queue<Task>>();
    Workers _workers;

public:

    ThreadPool(int num_threads)
    {
        _numThreads = num_threads;
    }

    void queueEvent(const Task& evt)
    {
        _task_queue->push(evt);
    }

    void initialiseWorker(Worker::Ptr& worker_)
    {
        worker_->initialise(_task_queue);
        _workers.push_back(std::move(worker_));
    }

};

}
#endif
