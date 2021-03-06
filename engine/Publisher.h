#ifndef PUBLISHER_H
#define PUBLISHER_H

// boost
#include <boost/tokenizer.hpp>

// STL
#include <iostream>     // cout, endl
#include <fstream>      // fstream
#include <vector>
#include <string>
#include <algorithm>    // copy
#include <iterator>     // ostream_operator
#include <memory>
#include <mutex>

#include <logger.h>

// sources
#include "Event.h"

#include "include.hpp"
#include "Subscriber.h"
#include "ThreadPool.h"
#include "Threaded.h"

namespace engine
{

using namespace domain;

template<class DataType>
class Publisher : public Threaded
{
typedef boost::tokenizer<boost::escaped_list_separator<char>> Tokenizer;

private:
    std::mutex                      _run_lock;
    std::thread                     _thread;
    std::shared_ptr<ThreadPool>     _threadPool;
    GETSET(std::string,             connectionString);
    GETSET(bool,                    paused);
    GETSET(int,                     time);
    GETSET(int,                     msgNum);
    GETSET(int,                     increment);


public:

    Publisher(std::shared_ptr<ThreadPool> threadPool_,
              const std::string& connectionString)
    :   _run_lock()
    ,   _thread()
    ,   _threadPool(threadPool_)
    ,   _connectionString(connectionString)
    ,   _paused()
    ,   _time()
    ,   _msgNum(0)
    ,   _increment(1)
    {
        LOG_INFO("publisher for " << connectionString << " created.");
    }


    

private:
    virtual const void updateSubscribers(const std::shared_ptr<const DataType>& data_)
    {
        _threadPool->queueEvent<DataType>(data_);
        LOG_DEBUG(std::this_thread::get_id() <<" added event");
        _msgNum++;
    }

    virtual void recordTime(const std::shared_ptr<const DataType>& data_)
    {
        switch(data_->gettimeType())
        {
            case TimeType::Continuous:
            {
                setlatestTime(_msgNum*_increment);
                break;
            }
            case TimeType::Linked:
            {
                setlatestTime(linkedThread()->getlatestTime());
                break;
            }
            case TimeType::Stamped:
            {
                setlatestTime(data_->gettimestamp());
                break;
            }
        }
    }

    virtual bool connect()
    {
        return true;
    }

    virtual void run()
    { 
        std::string line;
        std::ifstream in(_connectionString);
        if (!in.is_open())
        {
            return;
        }
        while (getline(in,line))
        {
            while (isPaused())
            {
                // spin here if paused
            }
            std::vector<std::string> vec;
            Tokenizer tok(line);
            vec.assign(tok.begin(),tok.end());
            auto data = std::make_shared<const DataType>(vec);
            updateSubscribers(data);
            recordTime(data);
            if (vec.size() < 3){
                continue;
            }
        }
        LOG_INFO("Publisher finished");
    }
};

} // engine

#endif
