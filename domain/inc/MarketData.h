#pragma once

#include <string>
#include <vector>

#include <include.hpp>



namespace domain {

class MarketData
    :public Data
{

public:
    typedef std::vector<Quote> Quotes;

    GETSET(Quotes, bids);
    GETSET(Quotes, asks);
    GETSET(int, levels);

    MarketData(const std::vector<std::string>& data, const int n_levels);
    inline const Quote& askLevel(int level) const;
    
    inline const Quote& bidLevel(int level) const;


    std::ostream& operator<<(std::ostream& out);

};

}
