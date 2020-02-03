#pragma once

#include <include.hpp>
#include <iostream>

namespace domain
{
using orderid_t = uint64_t;

class Quote
{
    GETSET(double, price);
    GETSET(int, quantity);
private:
    Side _side;

public:
    const Side getside() { return _side; }
    void setside(Side side) { _side = side; }
    std::ostream& operator<<(std::ostream& out);


};
}

