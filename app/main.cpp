#define BOOST_LOG_DYN_LINK 1 // necessary when linking the boost_log library dynamically
#include <iostream>
// engine
#include <Publisher.h>
#include <memory>
#include <ThreadPool.h>
#include <MarketData.h>
#include <Subscriber.h>
#include <thread>
#include <PublisherController.h>
#include <mutex>
#include <logger.h>

using namespace engine;

int main (void)
{
   std::vector<Worker::Ptr> strategies;
   auto pool = std::make_shared<ThreadPool>(2);

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
