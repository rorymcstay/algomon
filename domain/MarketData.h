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

    GETSET(Quotes, bids);
    GETSET(Quotes, asks);
    GETSET(int, levels);

    MarketData(const std::vector<std::string>& data);
    inline const Quote& askLevel(int level) const 
    {
        return _asks[level];
    }
    inline const Quote& bidLevel(int level) const
    {
        return _bids[level];
    }
};

inline std::ostream& operator << (std::ostream& out, const MarketData& md)
{
    int level = 1;
    while (level <= md.getlevels())
    {
        out << "level: " << md.askLevel(level-1);
        level++;
    }
    return out;
}

inline std::ostream& operator << (std::ostream& out, const MarketData* md)
{
    int level = 1;
    while (level <= md->getlevels())
    {
        out << "level: " << md->askLevel(level-1);
        level++;
    }
    return out;
}

}


#endif
