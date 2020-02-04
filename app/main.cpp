#include <iostream>
// engine
#include <Publisher.h>

#include <MarketData.h>

using namespace engine;

int main (void)
{
   LOG("hello");
   Publisher<domain::MarketData> publisher("string");
   publisher.run();

}
