#include <string>
#include <vector>

#include "include.hpp"
#include "Subscriber.h"


namespace engine
{

template<typename DataType>
class Publisher
{

public:

    using Subscribers = std::vector<Subscriber::Ptr>;
    
    GETSET(std::string, connectionString);
    GETSET(Subscribers, subscribers);

public:

    Publisher()
    {
        _subscribers.clear();
    };



public:
    void run () const;

    void addSubscriber(Subscriber::Ptr subscriber)
    {
        _subscribers.push_back(std::move(subscriber));
    }
 
    void notifySubscribers(const Event<DataType>& event_)
    {
        for (auto& subscriber : _subscribers)
        {
            subscriber->onEvent(event_.getPointer());
        }
    }
};

