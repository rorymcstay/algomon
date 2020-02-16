#ifndef WORKER_H
#define WORKER_H

#include <thread>
#include <queue>
#include <memory>
#include <mutex>

#include <include.hpp>
#include <logger.hpp>

//domain
#include <MarketData.h>
#include <TradeMessage.h>

// engine
#include "Task.h"
#include "Threaded.h"


#define REGISTER_EVENT(eventType)\
private:\
    virtual void onEvent(const std::shared_ptr<eventType>& evt_)\
    {\
        LOG(evt_);\
    }

namespace engine
{
class Worker : public Threaded
{
private:

    std::mutex _lock;
    std::queue<Task> _queue;
    std::thread _thread;
    GETSET(std::string, name)
    REGISTER_EVENT(domain::MarketData)
    REGISTER_EVENT(domain::TradeMessage)
    
    void onEvent(const Task& evt)
    {
        LOG("onEvent");
        if (evt.md)
        {
            onEvent(evt.md);
        }
        if (evt.tm)
        {
            onEvent(evt.tm);
        }
    }

public:
    using Ptr = std::unique_ptr<Worker>;
    Worker(const std::string& name_)
    :   _name(name_)
    {
    }
    
    void init()
    {
    }

    std::mutex& getlock()
    {
        return _lock;
    }



    template<class DataType>
    void addTask(const std::shared_ptr<DataType>& evt)
    { 
        PREP_LOCK_DEBUG() 
        std::lock_guard<std::mutex> lk1(_lock, std::adopt_lock);
        LOCK_DEBUG();
        _queue.emplace(evt);
        std::this_thread::sleep_for(std::chrono::milliseconds(100000));
    }

    void handleEvent()
    {
        PREP_LOCK_DEBUG()
        std::lock_guard<std::mutex> lck(_lock);
        LOCK_DEBUG("Worker::handleEvent");
        const Task& task = _queue.front();
        onEvent(task);
        _queue.pop();
    }

    void run()
    {
        while (true)
        {
            if (!_queue.empty())
            {
                handleEvent();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }
};
}
#endif
