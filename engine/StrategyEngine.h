#ifndef STRATEGYENGINE_H
#define STRATEGYENGINE_H
#include <string>
#include <map>
#include <fix8/f8includes.hpp>
#include <FIX44_types.hpp>
#include <FIX44_router.hpp>
#include <FIX44_classes.hpp>

#include "ConfigManager.h"


namespace engine 
{

class SessionImpl;
class Strategy;
class Allocation;
using StrategyPtr = std::shared_ptr<Strategy>;
using AllocationPtr = std::shared_ptr<Allocation>;

// TODO extract fix44 types to includes. using FIX44_Router = FIXRouter
class StrategyEngine : public FIX8::FIX44::FIX44_Router
{

public:
    using Ptr=std::shared_ptr<StrategyEngine>;

    StrategyEngine(SessionImpl& session_);

    ~StrategyEngine(){};
    void initialise(cfg::ConfigManager::Ptr configManager_);
    const StrategyPtr& getOrCreateStrategy(const std::string& key);
    const StrategyPtr getStrategyPtr(const std::string& key) const;
    const StrategyPtr& getStrategyByMessage(const FIX8::Message* msg) const;

private:
    SessionImpl&                            _session;
    cfg::ConfigManager::Ptr                 _configManager;
    std::map<std::string, StrategyPtr>      _strategies;
    GETSET(bool,                            enforceSeqCheck)
    GETSET(domain::StrategyKey,             strategykey);

    bool sendOrderSingle(AllocationPtr& alloc_);

public:
    virtual bool operator() (const FIX8::FIX44::ExecutionReport *msg) const;
    virtual bool operator() (const FIX8::FIX44::NewOrderSingle* msg) const;


    
};

}

#endif
