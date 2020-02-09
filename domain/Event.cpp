#include "Event.h"


namespace domain
{
std::ostream& operator <<(std::ostream& out, Event& event)
{
    out << enum2str(event.gettype());
}
}
