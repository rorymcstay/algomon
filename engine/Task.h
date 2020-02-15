#include <memory>

#include <MarketData.h>
#include <TradeMessage.h>


namespace engine
{
#define REGISTER_CONTEXT(type, name)\
    std::shared_ptr<type> name;\
    Task(std::shared_ptr<type> evt)\
    {\
        name = evt;\
    }
        
struct Task
{
    REGISTER_CONTEXT(domain::MarketData, md)
    REGISTER_CONTEXT(domain::TradeMessage, tm)
};
}
