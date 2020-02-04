#ifndef EVENT_H
#define EVENT_H

#include <include.hpp>
#include <iostream>
#include <memory>

#include <Enums.h>

using namespace domain;

namespace engine
{

template<typename T>
class Event
{

public:
    using Ptr = std::shared_ptr<Event>;
 
    GETSET(domain::EventType, type);
    typename T::Ptr _data;

    Event(const std::unique_ptr<T>& data_)
    :   _data(std::move(data_))
    {
    }

    std::ostream& operator <<(std::ostream& out)
    {
        out << enum2str(_type);
    }

};



} //publisher

#endif
