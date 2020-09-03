#include "SessionImpl.h"
#include "StrategyEngine.h"

namespace engine
{

SessionImpl::SessionImpl(
        cfg::ConfigManager::Ptr configManager_,
        const FIX8::F8MetaCntx& ctx, 
        const FIX8::SessionID& sid, 
        FIX8::Persister *persist,
        FIX8::Logger *logger, 
        FIX8::Logger *plogger)
:   Session(ctx, sid, persist, logger, plogger)
,   _strategyEngine(*this, configManager_)
{
}

bool SessionImpl::handle_application(const unsigned int seq, const FIX8::Message*& msg)
{
    return enforce(seq, msg) || msg->process(_strategyEngine);  
}


}
