#include "Event.h"


namespace domain
{
std::ostream& operator <<(std::ostream& out, Event& event)
{
    return out << enum2str(event.gettype());
}
}
