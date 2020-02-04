#ifndef PUBLISHER_H
#define PUBLISHER_H

// boost
#include <boost/tokenizer.hpp>

// STL
#include <iostream>     // cout, endl
#include <fstream>      // fstream
#include <vector>
#include <string>
#include <algorithm>    // copy
#include <iterator>     // ostream_operator

// sources
#include "Event.h"

#include "include.hpp"
#include "Subscriber.h"


namespace engine
{

template<typename DataType>
class Publisher
{
typedef boost::tokenizer<boost::escaped_list_separator<char>> Tokenizer;
public:

    using Subscribers = std::vector<Subscriber::Ptr>;
    
    GETSET(std::string, connectionString);
    GETSET(Subscribers, subscribers);

public:

    Publisher(const std::string& connectionString)
    {
        _subscribers.clear();
        _connectionString = connectionString;
    }



public:
    void run() const
    {
        std::ifstream in(_connectionString);
        if (!in.is_open()) return;

        thread_local std::vector<std::string> vec;

        vec.reserve(5);
        std::string line;

        while (getline(in,line))
        {
            Tokenizer tok(line);
            vec.assign(tok.begin(),tok.end());
            std::unique_ptr<DataType> data = std::make_unique<DataType>(vec);
            Event<DataType> event(data);

            notifySubscribers(event);

            if (vec.size() < 3) continue;

        }
    }

    void addSubscriber(Subscriber::Ptr subscriber)
    {
        _subscribers.push_back(std::move(subscriber));
    }
 
    void notifySubscribers(Event<DataType> event_)
    {
        for (auto& subscriber : _subscribers)
        {
            subscriber->onEvent(event_.getPointer());
        }
    }
};

} // engine

#endif
