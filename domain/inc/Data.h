#pragma once

#include <include.hpp>
#include <memory>

namespace domain
{


class Data
{
public:
    typedef std::unique_ptr<Data> Ptr;
     
    Data()
    {
        _ptr = std::make_unique<Data>();
    }
private:
    Ptr _ptr;
};

}
