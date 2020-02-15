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

    void onEvent(const std::shared_ptr<domain::MarketData>& md)
    {
        for (int i = 0; i < md->getlevels()-1; i++)
        {
            const Quote& quote = md->askLevel(i);
            LOG("ask level " << i <<   ": " << quote);
        }
    }

};
}

#endif
