#include <iostream>
#include <logger.hpp>
#include <Publisher.h>

using namespace publisher;

int main (void){
   LOG("hello");
   Publisher publisher = Publisher();
   publisher.dumpFile();

}
