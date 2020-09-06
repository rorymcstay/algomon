#define BOOST_LOG_DYN_LINK 1 // necessary when linking the boost_log library dynamically

#include "TestEnvironment.h"
#include "ConfigManager.h"


int main(int argc, char* argv[])
{
    auto configManager = std::make_shared<cfg::ConfigManager>();
    std::string strategy_config_file = "config/main.xml";
    configManager->initialise(strategy_config_file);
    auto env = testfwk::TestEnvironment(configManager);
}
