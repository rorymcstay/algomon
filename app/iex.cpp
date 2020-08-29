#define BOOST_LOG_DYN_LINK 1 // necessary when linking the boost_log library dynamically
#include <../iex_provider/IEXProvider.h>


int main(void)
{
    iex_provider::IEXProvider::run();
}

