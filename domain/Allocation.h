#ifndef ALLOCATION_H
#define ALLOCATION_H
#include <string>
#include <memory>
#include <ostream>
#include <Enums.h>

#include <logger.h>

namespace domain
{
using price_t = double;
using qty_t = int;
using symbol_t = std::string;

class Allocation
{
private:
    GETSET(price_t,             price);
    GETSET(qty_t,               qty);
    GETSET(domain::Side,        side);
    GETSET(symbol_t,            symbol);
public:
    using Ptr = std::shared_ptr<Allocation>;
    Allocation(price_t price_, qty_t qty_, domain::Side side_, symbol_t& symbol_)
    :   _price(price_)
    ,   _qty(qty_)
    ,   _side(side_)
    ,   _symbol(symbol_)
    {
        LOG_DEBUG("Created allocation: " << LOG_VAR(this));
    }

};

std::ostream& operator<<(std::ostream& stream_, Allocation::Ptr& alloc_)
{
    return stream_ << LOG_NVP("Price", alloc_->getprice()) 
                   << LOG_NVP("Qty", alloc_->getqty()) 
                   << LOG_NVP("Side", alloc_->getside()) 
                   << LOG_NVP("Symbol", alloc_->getsymbol());
}
}

#endif
