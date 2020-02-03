#include <string>
#include <boost/lockfree/queue.hpp>
#include "include.hpp"

namespace engine
{
class Subscriber
{
public:
    using Ptr = std::shared_ptr<Subscriber>;
 
    GETSET(Subscriptions, subscriptions);

private:
    boost::queue<Event::Ptr> queue;

    void onEvent(const Event<DataType>::Ptr&, event_)
    {
        LOG(event_);
        queue.push(event_);
    }

    void handleEvent(const Event::Ptr& item)
    {
        switch(item->type_)
        {
            case(EventType::MarketData)
            {
                LOG(item);
            }
            case(EventType::TradeMessage)
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
                Event::Ptr item;
                queue.pop(item);
                handleEvent(item);
            }
        }
    }
};
}
