#ifndef SESSIONIMPL_H
#define SESSIONIMPL_H
#include <fix8/f8includes.hpp>
#include <FIX44_types.hpp>
#include <FIX44_router.hpp>
#include <FIX44_classes.hpp>

#include "ConfigManager.h"
#include "StrategyEngine.h"

namespace engine
{

class SessionImpl : public FIX8::Session
{
private:
    StrategyEngine      _strategyEngine;
public:
    SessionImpl(
         cfg::ConfigManager::Ptr configManager_,
         const FIX8::F8MetaCntx& ctx,
         const FIX8::SessionID& sid,
         FIX8::Persister* persist=nullptr,
         FIX8::Logger* logger=nullptr,
         FIX8::Logger* plogger=nullptr);
    virtual bool handle_application(const unsigned int seq, const FIX8::Message*& msg) override;
};

}

#endif
