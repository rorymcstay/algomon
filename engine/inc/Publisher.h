#include <string>
#include <boost/lockfree/queue.hpp>
#include "include.hpp"
#include "Subscriber.h"

namespace engine
{

template<DataType>
class Publisher
{

public:
    Publisher()
    {
        _subsrcibers.clear();
    };

    GETSET(std::string, connectionString);
    GETSET(std::vector<Subscriber::Ptr>(5), subscribers);

public:
    void run () const;

    void addSubscriber(const Subscriber subscriber)
    {
        Subscriber::Ptr subscriber;
        _subscribers.push_back(subscriber);
    }
 
    void notifySubscribers(const Event<DataType>& event_)
    {
        for (auto& subscriber : _subscribers)
        {
            _subscribers->onEvent(event_.getPointer());
        }
    }
};

