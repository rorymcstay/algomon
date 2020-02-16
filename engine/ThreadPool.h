#ifndef THREADPOOL_H
#define THREADPOOL_H
#include <thread>
#include <queue>
#include <vector>
#include <mutex>
#include <functional>
#include <map>
#include <memory>
//#include <Event.h>

#include <logger.h>
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
    
    using Workers = std::map<std::string, Worker::Ptr>;

    int _numThreads;
    std::mutex _lock;
    Workers _workers;

public:

    ThreadPool(int num_threads)
    {
        _numThreads = num_threads;
    }

    std::mutex& getlock()
    {
        return _lock;
    }
 
    template<class DataType>
    void queueEvent(const std::shared_ptr<const DataType>& event)
    {
        for (auto& worker : _workers)
        {
            worker.second->addTask<DataType>(event);
        }
    }

    template<class T>
    void initialiseWorker(const std::string& name_)
    {
        _workers.emplace(name_, std::make_unique<T>(name_));
        _workers[name_]->init();
        _workers[name_]->initalise();
    }

    void finalised()
    {
        for( auto& worker : _workers)
        {
            LOG_DEBUG("Joining thread " << worker.first);
            worker.second->join();
        }
    }

};

}
#endif
