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

namespace engine
{

using namespace domain;

template<class DataType>
class Publisher
{
typedef boost::tokenizer<boost::escaped_list_separator<char>> Tokenizer;

private:
    GETSET(std::string, connectionString);
    GETSET(std::shared_ptr<ThreadPool>, threadPool);

public:

    Publisher(std::shared_ptr<ThreadPool> threadPool_,const std::string& connectionString)
    :   _threadPool(threadPool_)
    ,   _connectionString(connectionString)
    {
    }


    void run()
    {
        std::ifstream in(_connectionString);
        if (!in.is_open()) return;

        thread_local std::vector<std::string> vec;

        vec.reserve(5);
        std::string line;

        while (getline(in,line))
        {
            Tokenizer tok(line);
            vec.assign(tok.begin(),tok.end());
            typename std::shared_ptr<DataType> event = std::make_shared<DataType>(vec);
            Task task(event); 
            _threadPool->queueEvent(task);

            if (vec.size() < 3) continue;

        }
    }
 
};

} // engine

#endif
