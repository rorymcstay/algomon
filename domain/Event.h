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
 
    GETSET(EventType, type);

public:


};




} //domain

#endif
