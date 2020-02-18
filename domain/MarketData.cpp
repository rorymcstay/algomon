#include "Enums.h"
#include "Quote.h"

#include "MarketData.h"


namespace domain
{
    MarketData::MarketData(const std::vector<std::string>& data)
    :   Event(EventType::MarketData, TimeType::Linked)
    {
        int level(1);
        int i(0);
        _levels = 30;
        _asks.reserve(_levels);
        _bids.reserve(_levels);
        while (level < _levels)
        {
            Quote ask = Quote();
            ask.setprice(utils::fromString<double>(data[i]));
            ask.setquantity(utils::fromString<int>(data[i+1]));
            ask.setside(Side::Sell);

            Quote bid = Quote();
            bid.setprice(utils::fromString<double>(data[i + 2]));
            bid.setquantity(utils::fromString<int>(data[i+3]));
            bid.setside(Side::Buy);

            _asks[level - 1] = ask;
            _bids[level - 1] = bid;
            level ++;
            i += 4;
        }
    }

}
