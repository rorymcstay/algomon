#include "../../utils.include.h"

class Quote
{
    GETSET(int, quantity);
    GETSET(double, price);
    
    QUOTECOMP(price);
}

