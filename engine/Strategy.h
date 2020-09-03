//std
#include <memory>

// fix44
#include <fix8/f8includes.hpp>
#include <FIX44_types.hpp>
#include <FIX44_router.hpp>
#include <FIX44_classes.hpp>

//utils
#include <include.hpp>
#include <logger.h>

//domain
#include <EvalContext.h>
#include <Allocation.h>


using namespace FIX8;
namespace engine
{

class StrategyEngine;

class Strategy
{
friend StrategyEngine;
private:
    std::string                 _name;

protected:

public:
    Strategy(const std::string& name_);
    ~Strategy(){};
    using Ptr = std::shared_ptr<Strategy>;

    // interface
    virtual bool evaluate(const EvalContext::Ptr& msg) const
    {
        LOG_DEBUG(msg->getmsg());
        return true;
    }

    bool const addAllocation(domain::Allocation::Ptr alloc_){ return true; }

};

}
