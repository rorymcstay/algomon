#define BOOST_LOG_DYN_LINK 1 // necessary when linking the boost_log library dynamically
// std
#include <iostream>
#include <memory>
#include <thread>
#include <mutex>

// engine
#include <Publisher.h>
#include <ThreadPool.h>
#include <MarketData.h>
#include <Subscriber.h>
#include <PublisherController.h>
#include <ConfigManager.h>

//utils
#include <logger.h>
#include "cli_opts.h"


//CLI Opts
#define CONFIG_FILE     "--config-file"
#define DRY_RUN         "--dry-run"

using namespace engine;

int main (int argc, char* argv[])
{
    auto cli_parser = InputParser(argc, argv);
    if (!cli_parser.cmdOptionExists(CONFIG_FILE))
    {
        LOG_INFO("No --configfile specified.");
        return 0;
    }

    std::string configfile_ = cli_parser.getCmdOption(CONFIG_FILE);
    auto configManager = std::make_shared<cfg::ConfigManager>();
    configManager->initialise(configfile_);
    if (cli_parser.cmdOptionExists(DRY_RUN))
    {
        LOG_INFO("Dry run specified, exiting");
        return 0;
    }


    auto pool = std::make_shared<ThreadPool>(2);
 
    std::vector<Worker::Ptr> strategies;


    auto marketData = std::make_shared<Publisher<domain::MarketData>>(pool, "/home/rory/dev/algo/lobster_sample/AAPL_2012-06-21_34200000_37800000_orderbook_30.csv");
    auto tradeMessages = std::make_shared<Publisher<domain::TradeMessage>>(pool, "/home/rory/dev/algo/lobster_sample/AAPL_2012-06-21_34200000_37800000_message_30.csv");


    PublisherController controller = PublisherController();
    controller.addPublisher(marketData, EventType::MarketData);
    pool->initialiseWorker<Subscriber>("subscriber");
    controller.addPublisher(tradeMessages, EventType::TradeMessage);
    //controller.linkPublishers(EventType::TradeMessage, EventType::MarketData);
    controller.linkPublishers(EventType::MarketData, EventType::TradeMessage);

    controller.runPublishers();
    pool->finalised();


}
