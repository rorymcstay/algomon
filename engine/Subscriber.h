#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H

// STL
#include <string>
#include <queue>

// Utils
#include <include.hpp>
#include <logger.h>

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
        LOG_INFO(getname() << "best ask " << md->askLevel(0) << " best bid " << md->bidLevel(0));
    }

    void onEvent(const std::shared_ptr<const domain::TradeMessage>& tm) override
    {
        LOG_INFO("trade message: " << tm);
    }
};
}

#endif
