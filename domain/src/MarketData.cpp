#include "Enums.h"
#include "Quote.h"
#include "Data.h"

#include "MarketData.h"


namespace domain
{
    MarketData::MarketData(const std::vector<std::string>& data)
    {
        int level(1);
        int i(0);
        _levels = 5;
        while (level < _levels)
        {
            Quote ask = Quote();
            ask.setprice(std::stod(data[i]));
            ask.setquantity(std::stoi(data[i+1]));
            ask.setside(Side::Sell);

            Quote bid = Quote();
            bid.setprice(std::stod(data[i + 2]));
            bid.setquantity(std::stoi(data[i+3]));
            bid.setside(Side::Buy);

            _asks[i] = ask;
            _bids[i] = bid;
            level ++;
            i += 4;
        }
    }
    inline const Quote& MarketData::askLevel(int level) const
    {
        return _asks[level];
    }

    inline const Quote& MarketData::bidLevel(int level) const
    {
        return _bids[level];
    }
    std::ostream& MarketData::operator<<(std::ostream& out)
    {
        int level = 1;
        while (level <= _levels)
        {
            out << "level: " << level; 
        }
    }
}
