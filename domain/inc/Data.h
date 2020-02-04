#ifndef DATA_H
#define DATA_H

#include <include.hpp>
#include <memory>
#include "Enums.h"

namespace domain
{


class Data
{
public:
    typedef std::unique_ptr<Data> Ptr;

    GETSET(EventType, type);

public:
    Data()
    {
        _ptr = std::make_unique<Data>();
    }
    

private:
    Ptr _ptr;
};

}

#endif
