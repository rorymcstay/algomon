#ifndef ENUMS_H
#define ENUMS_H

#include <include.hpp>

using namespace utils;
namespace domain
{
    ENUM_MACRO_2(Side, Buy, Sell);
    ENUM_MACRO_2(EventType, MarketData, TradeMessage);
    ENUM_MACRO_3(TimeType, Continuous, Linked, Stamped);
    ENUM_MACRO_7(MessageType, NewOrder, Cancel, Deletion, Execution, HiddenExecution, TradingHalt, Unknown)
    ENUM_MACRO_5(EvalEventType, Trade, ExecMsg, MDEvent, Request, AnalyticEvent);
    ENUM_MACRO_2(StrategyKey, Instrument, Order);
}

#endif // ENUMS_H
