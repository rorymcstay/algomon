#define BOOST_LOG_DYN_LINK 1 // necessary when linking the boost_log library dynamically

#include "TestEnvironment.h"
#include "ConfigManager.h"


int main(int argc, char* argv[])
{
    auto configManager = std::make_shared<cfg::ConfigManager>();
    FIX8::GlobalLogger::set_global_filename("test.fix");
    std::string strategy_config_file = "config/main.xml";
    configManager->initialise(strategy_config_file);
    auto env = testfwk::TestEnvironment(configManager);
    env << "UPSTREAM NewOrderSingle Price=0.9 Symbol=AAPL ExDestination=NYSE OrderQty=1000";
}
