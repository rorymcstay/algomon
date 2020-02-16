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
    std::vector<DataType> _storage;
    GETSET(std::string, connectionString);

public:

    Publisher(std::shared_ptr<ThreadPool> threadPool_,const std::string& connectionString)
    :   _threadPool(threadPool_)
    ,   _storage(50000)
    ,   _connectionString(connectionString)
    {

        LOG("publisher for " << connectionString << " created.");
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
            _storage.emplace_back(vec);
            _threadPool->queueEvent<DataType>(std::shared_ptr<DataType>(_storage.end()));
    //        LOG(std::this_thread::get_id() <<" added event");
            std::this_thread::sleep_for(std::chrono::milliseconds(100));

            if (vec.size() < 3) continue;

        }
    }
 
};

} // engine

#endif
