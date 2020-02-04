#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

#include <string>
#include <queue>
#include <include.hpp>
#include <Data.h>
#include <logger.hpp>

#include "Event.h"


namespace engine
{
class Subscriber
{
public:
    using Ptr = std::shared_ptr<Subscriber>;
    using EventPtr = std::shared_ptr<Event<Data>>;

private:
    std::queue<EventPtr> queue;

    void onEvent(const EventPtr& event_)
    {
        LOG(event_);
        queue.push(event_);
    }

    void handleEvent(const EventPtr& item)
    {
        switch(item->gettype())
        {
            case EventType::MarketData:
            {
                LOG(item);
                break;
            }
            case EventType::TradeMessage:
            {
                LOG(item);
            }
        }
    }

    void run()
    {
        while (true)
        {
            if (!queue.empty())
            {
                const Event<Data>::Ptr& item = queue.front();
                handleEvent(item);
                queue.pop();
            }
        }
    }
};
}

#endif
