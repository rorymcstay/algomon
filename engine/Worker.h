#ifndef WORKER_H
#define WORKER_H

#include <thread>
#include <queue>
#include <memory>
#include <mutex>

#include <include.hpp>
#include <logger.h>

//domain
#include <MarketData.h>
#include <TradeMessage.h>

// engine
#include "Task.h"
#include "Threaded.h"


#define REGISTER_EVENT(eventType)\
private:\
    virtual void onEvent(const std::shared_ptr<const eventType>& evt_)\
    {\
        LOG_INFO(evt_);\
    }

namespace engine
{

class Worker : public Threaded
{
private:

    mutable std::mutex      _queue_lock;
    std::queue<Task>        _queue;
    std::thread             _thread;
    GETSET(std::string,     name)

    REGISTER_EVENT(domain::MarketData)
    REGISTER_EVENT(domain::TradeMessage)
    
    void onNewTask(Task evt)
    {
        if (evt.md)
        {
            onEvent(evt.md);
        }
        if (evt.tm)
        {
            onEvent(evt.tm);
        }
    }
 
    void handleEvent()
    {
        std::lock_guard<std::mutex> lck(_queue_lock, std::adopt_lock);
        const Task& task = _queue.front();
        LOG_DEBUG("have new task, queue is of length " << _queue.size());
        onNewTask(task);
    }

    void removeEvent()
    {
        std::lock_guard<std::mutex> lck(_queue_lock, std::adopt_lock);
        _queue.pop();
    }

    void run()
    {
        while (true)
        {
            if (!_queue.empty())
            {
                handleEvent();
                removeEvent();
            }
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
        return _queue_lock;
    }

    template<class DataType>
    void addTask(const std::shared_ptr<const DataType>& evt)
    { 
        std::lock_guard<std::mutex> lk1(_queue_lock, std::adopt_lock);
        _queue.emplace(evt);
    } 
};
}
#endif
