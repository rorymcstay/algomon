#ifndef PUBLISHERCONTROLLER_H
#define PUBLISHERCONTROLLER_H

#include <Enums.h>
#include "Publisher.h"
#include "Threaded.h"
#include <logger.h>
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
    void linkPublishers(domain::EventType leader_, domain::EventType follower_)
    {
        if(_publishers.find(follower_) != _publishers.end() && _publishers.find(leader_) != _publishers.end())
        {            
            _publishers[leader_]->setlinkedThread(_publishers[follower_]);
        }
        else
        {
            LOG_ERROR("Publishers not initialised.");
        }
    }

    void runPublishers()
    {
        for (auto& pub : _publishers)
        {
            std::string thread_name = enum2str(pub.first);
            pub.second->initalise(thread_name);
        }
    }
};

}

#endif
