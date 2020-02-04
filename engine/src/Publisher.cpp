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

// sources
#include "Event.h"

namespace engine
{

typedef boost::tokenizer<boost::escaped_list_separator<char>> Tokenizer;

template<typename DataType>
void Publisher<DataType>::run() const
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
        DataType data(vec);
        Event<DataType> event(data.getdata());

        notifySubscribers(event);

        if (vec.size() < 3) continue;

    }
}

} // publisher
