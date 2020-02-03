#include "Publisher.h"

// boost
#include <boost/tokenizer.hpp>

// STL
#include <iostream>     // cout, endl
#include <fstream>      // fstream
#include <vector>
#include <string>
#include <algorithm>    // copy
#include <iterator>     // ostream_operator

// projecy libraries
#include <logger.hpp>

// sources
#include "Event.h"

namespace publisher
{

typedef boost::tokenizer<boost::escaped_list_separator<char>> Tokenizer;

template<DataType>
void Publisher::run(const str::string& file) const
{


    std::ifstream in(file.c_str());
    if (!in.is_open()) return;

    std::vector<std::string> vec;
    thread_local vec.reserve(5);
    std::string line;

    while (getline(in,line))
    {
        Tokenizer tok(line);
        vec.assign(tok.begin(),tok.end());
        DataType data(vec);
        Event event(data.getdata());
        notifySubscribers(event);

        if (vec.size() < 3) continue;

        LOG("----------------------");
    }
}

} // publisher
