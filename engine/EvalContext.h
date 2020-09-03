
#include <fix8/f8includes.hpp>
#include <FIX44_types.hpp>
#include <FIX44_router.hpp>
#include <FIX44_classes.hpp>
#include <include.hpp>
#include <Enums.h>

using namespace FIX8;

namespace engine {


class EvalContext
{
private:
    GETSET(domain::EvalEventType,             eventType)
    const FIX8::Message*                      _msg;

public:
    using Ptr = std::unique_ptr<EvalContext>;
    EvalContext(domain::EvalEventType eventType_, const FIX8::Message* msg=nullptr)
    :   _eventType(eventType_)
    ,   _msg(msg)
    {

    }

    const FIX8::Message* getmsg() const { return _msg; };
    
};


}
