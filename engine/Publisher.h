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
    std::thread _thread;
    std::shared_ptr<ThreadPool> _threadPool;
    GETSET(std::string, connectionString);

public:

    Publisher(std::shared_ptr<ThreadPool> threadPool_,const std::string& connectionString)
    :   _threadPool(threadPool_)
    ,   _connectionString(connectionString)
    {
        LOG_INFO("publisher for " << connectionString << " created.");
    }

private:
    void run()
    {
        std::ifstream in(_connectionString);
        if (!in.is_open()) return;
    
        std::string line;

        while (getline(in,line))
        {
            std::vector<std::string> vec;
            Tokenizer tok(line);
            vec.assign(tok.begin(),tok.end());
            auto data = std::make_shared<const DataType>(vec);
            _threadPool->queueEvent<DataType>(data);
            LOG_DEBUG(std::this_thread::get_id() <<" added event");

            if (vec.size() < 3) continue;

        }
    }
 
};

} // engine

#endif
