#ifndef TRADEMESSAGE_H
#define TRADEMESSAGE_H

#include "Event.h"
#include "Quote.h"

namespace domain
{
class TradeMessage: public Event
{
    typedef int orderid_t;
    GETSET(MessageType, type);
    GETSET(orderid_t, oid);
    GETSET(double, timestamp);
    GETSET(Quote, quote);

public:
    TradeMessage(std::vector<std::string> data_);


};


inline std::ostream& operator<<(std::ostream& out, const TradeMessage& msg)
{
    return out << "Message type: " << enum2str(msg.gettype());
}
inline std::ostream& operator<<(std::ostream& out, const TradeMessage* msg)
{
    return out << "Message type: " << enum2str(msg->gettype());
}

}

#endif
