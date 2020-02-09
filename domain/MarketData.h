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
    inline const Quote& askLevel(int level) const;
    
    inline const Quote& bidLevel(int level) const;


    std::ostream& operator<<(std::ostream& out);

};

}

#endif
