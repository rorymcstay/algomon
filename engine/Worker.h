#ifndef WORKER_H
#define WORKER_H

#include <thread>
#include <queue>
#include <memory>

#include <include.hpp>
#include <logger.hpp>

//domain
#include <MarketData.h>
#include <TradeMessage.h>

// engine
#include "Task.h"

#define REGISTER_EVENT(eventType)\
private:\
    virtual void onEvent(const std::shared_ptr<eventType>& evt_)\
    {\
        LOG(evt_);\
    }

namespace engine
{
class Worker
{
private:

    std::shared_ptr<std::queue<Task>> _queue;
    std::thread _thread;
    REGISTER_EVENT(domain::MarketData)
    REGISTER_EVENT(domain::TradeMessage)
    
    void onEvent(Task evt)
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

public:
    using Ptr = std::unique_ptr<Worker>;
    Worker()
    {
        
    }
    
    void initialise(std::shared_ptr<std::queue<Task>> queue)
    {
        _queue = queue;
        _thread = std::thread(&Worker::doTasks, this);
    }

    void doTasks()
    {
        while (true)
        {
            if (!_queue->empty())
            {
                Task task = _queue->front();
                onEvent(task);
                _queue->pop();
            }
        }
    }
};
}
#endif
