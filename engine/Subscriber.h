#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

// STL
#include <string>
#include <queue>

// Utils
#include <include.hpp>
#include <logger.hpp>

// Domain
#include <MarketData.h>
#include <Event.h>


using namespace domain;
namespace engine
{

class Subscriber
{
public:
    using Ptr = std::shared_ptr<Subscriber>;

private:
    std::queue<Event::Ptr> queue;

public:
    void onEvent(Event::Ptr event_)
    {
        LOG(enum2str(event_->gettype()));
        queue.push(event_);
    }

    void handleEvent(const Event::Ptr& item)
    {
        switch(item->gettype())
        {
            case EventType::MarketData:
            {
                LOG(enum2str(item->gettype()));
                break;
            }
            case EventType::TradeMessage:
            {
                LOG(enum2str(item->gettype()));
            }
        }
    }

    void run()
    {
        while (true)
        {
            if (!queue.empty())
            {
                const Event::Ptr& item = queue.front();
                handleEvent(item);
                queue.pop();
            }
        }
    }
};
}

#endif
