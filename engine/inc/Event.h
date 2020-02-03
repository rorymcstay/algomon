#include <include.hpp>
#include <iostream>
#include <Enums.h>
#include <Data.h>

using namespace domain;

namespace publisher
{

template<Data DataType>
class Event
{
public:
    using Ptr = shared_ptr<Event>;
    
    GETSET(DataType data);
    GETSET(MessageType, type);

    Event(DataType::Ptr dataPtr_)
    {
        _data = dataPtr_;
    }

    std::ostream& operator <<(ostream& out)
    {
        out << enum2str(type);
    }
    
    const std::shared_ptr std::getPointer() const
    {
       return make_shared<Event>(this);
    }

};




} //publisher
