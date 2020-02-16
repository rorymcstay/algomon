#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

// STL
#include <string>
#include <queue>

// Utils
#include <include.hpp>
#include <logger.hpp>

// Domain
#include <MarketData.h>
#include <Event.h>

#include "Worker.h"

using namespace domain;

namespace engine
{

class Subscriber : public Worker
{

public:
    using Ptr = std::shared_ptr<Subscriber>;

public:

    Subscriber(const std::string& name_)
    :   Worker(name_)
    {
        
    }

    void onEvent(const std::shared_ptr<const domain::MarketData>& md) override
    {
        
        LOG(getname() << " doing MarketData on event ");
        for (int i = 0; i < md->getlevels(); i++)
        {
            const Quote& quote = md->askLevel(i);
            LOG("ask level " << i <<   ": " << quote);
        }
    }

    void onEvent(const std::shared_ptr<const domain::TradeMessage>& tm) override
    {
        LOG(tm);
    }
};
}

#endif
