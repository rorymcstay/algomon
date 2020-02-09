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
    {
        _type = (MessageType)std::stoi(data_[1]);
        _oid = std::stoi(data_[3]);
        _timestamp = std::stod(data_[0]);

        // Quote
        Quote qt = Quote();
        qt.setprice(std::stod(data_[2]));
        qt.setquantity(std::stoi(data_[4]));

        switch(std::stoi(data_[5]))
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
