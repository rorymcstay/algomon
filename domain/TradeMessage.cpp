#include <vector>
#include <string>
#include <iostream>
#include <include.hpp>

#include "Enums.h"
#include "Quote.h"

#include "TradeMessage.h"

namespace domain
{
    TradeMessage::TradeMessage(std::vector<std::string> data_)
    :   Event(EventType::TradeMessage, TimeType::Stamped)
    {
        _type = (MessageType)utils::fromString<int>(data_[1]);
        _oid = utils::fromString<int>(data_[3]);
        settimestamp(utils::fromString<double>(data_[0]));

        // Quote
        Quote qt = Quote();
        qt.setprice(utils::fromString<double>(data_[2]));
        qt.setquantity(utils::fromString<int>(data_[4]));

        switch(utils::fromString<int>(data_[5]))
        {
            case 1:
            {
                qt.setside(Side::Buy);
                break;
            }
            case -1:
            {
                qt.setside(Side::Sell);
                break;
            }
        }
    }
}
