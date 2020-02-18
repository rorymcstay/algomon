#ifndef EVENT_H
#define EVENT_H

#include <include.hpp>
#include <iostream>
#include <memory>
#include <vector>

#include "Enums.h"




namespace domain
{

class Event
{

public:
    using Ptr = std::shared_ptr<Event>;
 
    Event(EventType type, TimeType tt)
    :   _timeType(tt)
    ,   _type(type)
    {
    }
    
    GETSET(TimeType, timeType);
    GETSET(EventType, type);

};




} //domain

#endif
