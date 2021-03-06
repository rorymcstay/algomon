#ifndef QUOTE_H
#define QUOTE_H

#include <include.hpp>
#include <iostream>
#include "Enums.h"


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
    Quote(){}
    ~Quote(){}
    Side getside() const { return _side; }
    void setside(Side side) { _side = side; }


};

inline std::ostream& operator<<(std::ostream& out, const Quote& qt )
{
    return out << enum2str(qt.getside()) << qt.getquantity() << "@" << qt.getprice();
}
inline std::ostream& operator<<(std::ostream& out, const Quote* qt )
{
    return out << enum2str(qt->getside()) << qt->getquantity() << "@" << qt->getprice();
}
}

#endif 
