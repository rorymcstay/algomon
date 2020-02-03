#include <include.hpp>

namespace domain
{
    ENUM_MACRO_2(Side, Buy, Sell);
    ENUM_MACRO_2(EventType, MarketData, TradeMessage);
    ENUM_MACRO_7(MessageType, NewOrder, Cancel, Deletion, Execution, HiddenExecution, TradingHalt, Unknown)
}
