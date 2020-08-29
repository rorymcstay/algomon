#include <IEX.h>
#include <logger.h>

namespace iex_provider
{
class IEXProvider
{

public:
    static void run()
    {
        Json::Value apple =  IEX::stocks::book("AAPL");
        LOG_INFO(apple.toStyledString());
    }
    
};
}
