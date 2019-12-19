#include <string>
#include <vector>

#include "Quote.h"
#include "../../utils/include.h"

namespace domain {
class MarketData
{
public:
    MarketData();
    GETSET(std::string, ticker)
    GETSET(int, levels)

private:
    std::vector<Quote> _bids;
    std::vector<Quote> _asks;

public:
    
    int bestAsk() const;
    int bestBid() const;
    int askLevel(int level) const;
    int bidLevel(int level) const;

};

}
