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

    // Test enums
    ENUM_MACRO_2(EnvSource, UPSTREAM, DOWNSTREAM);
    ENUM_MACRO_6(EnvMessageField, Price, Symbol, ExDestination, OrderQty, ExecType, TimeInForce);
    ENUM_MACRO_3(EnvMessageType, NewOrderSingle, ExecutionReport, MarketData );
}

#endif // ENUMS_H
