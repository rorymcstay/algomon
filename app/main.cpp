#include <iostream>
// engine
#include <Publisher.h>

using namespace engine;

int main (void)
{
   LOG("hello");
   Publisher<domain::Data> publisher("string");
   publisher.run();

}
