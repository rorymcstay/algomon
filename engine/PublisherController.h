#ifndef PUBLISHERCONTROLLER_H
#define PUBLISHERCONTROLLER_H

#include <Enums.h>
#include "Publisher.h"
#include "Threaded.h"
#include <map>

namespace engine
{
class PublisherController
{
public:

    std::map<domain::EventType, std::shared_ptr<Threaded>> _publishers;
    PublisherController()
    {

    }

    void addPublisher(std::shared_ptr<Threaded> publisher_, domain::EventType evt_)
    {
        _publishers[evt_] = publisher_;
    }

    void runPublishers()
    {
        for (auto& pub : _publishers)
        {
            pub.second->initalise();
        }
    }
};

}

#endif
