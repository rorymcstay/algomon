#include "Quote.h"
#include "MarketData.h"
#include "../../utils/include.h"

class Quote
{
friend MarketData;
    
    GETSET(int, price);
    GETSET(int, quantity);
    GETSET(int, direction);

}
