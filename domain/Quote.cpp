#include "Enums.h"
#include "Quote.h"

namespace domain
{
    std::ostream& Quote::operator<<(std::ostream& out)
    {
        out << enum2str(_side) << _quantity << "@" << _price;
    }
}
