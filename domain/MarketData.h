#ifndef MARKETDATA_H
#define MARKETDATA_H

#include <string>
#include <vector>

#include <include.hpp>

#include "Quote.h"
#include "Event.h"

namespace domain {

class MarketData : public Event
{



public:
    typedef std::vector<Quote> Quotes;
    Quote EMPTY_QUOTE;
private:
    GETSET(Quotes,          bids);
    GETSET(Quotes,          asks);
    GETSET(uint64_t,        levels);
public:
    MarketData(const std::vector<std::string>& data);
    ~MarketData(){}
    inline const Quote& askLevel(uint64_t level) const 
    {
        if (!_asks.empty() && _asks.size() <= level)
        {
            return _asks[level];
        }
        else
        {
            return EMPTY_QUOTE;
        }
    }
    inline const Quote& bidLevel(uint64_t level) const
    {
        if (!_bids.empty() && _bids.size() <= level)
        {
            return _bids[level];
        }
        else
        {
            return EMPTY_QUOTE;
        }
    }
};

inline std::ostream& operator << (std::ostream& out, const MarketData& md)
{
    uint64_t level = 1;
    while (level <= md.getlevels())
    {
        out << "level: " << md.askLevel(level-1);
        level++;
    }
    return out;
}

inline std::ostream& operator << (std::ostream& out, const MarketData* md)
{
    uint64_t level = 1;
    while (level <= md->getlevels())
    {
        out << "level: " << md->askLevel(level-1);
        level++;
    }
    return out;
}

}


#endif
