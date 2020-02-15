#include <iostream>
// engine
#include <Publisher.h>
#include <memory>
#include <ThreadPool.h>
#include <MarketData.h>
#include <Subscriber.h>

using namespace engine;

int main (void)
{
   LOG("hello");
   std::vector<Worker::Ptr> strategies;
   auto pool =  std::make_shared<ThreadPool>(2);
   Publisher<domain::MarketData> publisher(pool, "/home/rory/dev/algo/lobster_sample/AAPL_2012-06-21_34200000_37800000_orderbook_30.csv");
   strategies.emplace_back(new Subscriber());
   strategies[0];
   pool->initialiseWorker(strategies[0]);
   publisher.run();

}
