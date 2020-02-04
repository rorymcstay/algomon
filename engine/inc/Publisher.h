#ifndef PUBLISHER_H
#define PUBLISHER_H

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

    Publisher(const std::string& connectionString)
    {
        _subscribers.clear();
        _connectionString = connectionString;
    };



public:
    void run() const;

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

}

#endif
