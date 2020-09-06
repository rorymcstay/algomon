#include "StrategyEngine.h"
#include "ConfigManager.h"
#include "Strategy.h"

#include <fix8/f8includes.hpp>
#include <FIX44_types.hpp>
#include <FIX44_router.hpp>
#include <FIX44_classes.hpp>


using namespace cfg;
using namespace domain;

namespace engine {

StrategyEngine::StrategyEngine(SessionImpl& session_)
:   _session(session_)
{
}

const StrategyPtr& StrategyEngine::getStrategyByMessage(const FIX8::Message* msg) const
{
    switch(_strategykey)
    {
        case(StrategyKey::Instrument):
        {
            FIX8::FIX44::Symbol symbol;
            if (!msg->get(symbol))
                LOG_WARN("StrategyKey not found on message " << LOG_VAR(msg->get_msgtype()));
                return nullptr;
            LOG_DEBUG("Returning strategy for " << LOG_VAR(enum2str(_strategykey)) << LOG_VAR(symbol.get()));
            return getStrategyPtr(symbol.get()); 
        }
        case(StrategyKey::Order):
        case(StrategyKey::UnknownStrategyKey):
        {
            LOG_ERROR("Invalid strategy key loaded from config!"); 
            assert("Invalid strategy key loaded from config! " && false);
            return nullptr;
        }
    }
}

void StrategyEngine::initialise(
        cfg::ConfigManager::Ptr configManager_
)
{
    LOG_INFO("Initializing StrategyEngine");
    _configManager = configManager_;
    EngineConfig::Ptr engineConfig = _configManager->getengineConfig();
    _enforceSeqCheck = engineConfig->enforceSeqCheck;
    _strategykey = engineConfig->strategykey;

    for (auto& strategy : _configManager->getstrategyConfigs())
    {
        StrategyPtr stratPtr = getOrCreateStrategy(strategy.first);
        if (stratPtr)
        {
            LOG_INFO("Succesfully created strategy. " << LOG_VAR(strategy.first));
        }
        else
        {
            LOG_INFO("Failed to create strategy " << LOG_VAR(strategy.first));
        }
    }
}

const StrategyPtr StrategyEngine::getStrategyPtr(const std::string& name_) const
{
    if (_strategies.find(name_) != _strategies.end())
        return _strategies.at(name_);
    else
        return nullptr;
}

const StrategyPtr& StrategyEngine::getOrCreateStrategy(const std::string& name_)
{
    const auto& strat = getStrategyPtr(name_);
    if (strat)
        return strat;
    auto strategy = std::make_shared<Strategy>(name_);
    _strategies.insert(std::pair(name_, strategy));
    //strategy->initialise(); TODO
    return _strategies.at(name_);
}

bool StrategyEngine::operator() (const FIX8::FIX44::ExecutionReport *msg) const
{
    //TODO Make ExecutionMessage
    const StrategyPtr strat = getStrategyByMessage(msg);
    // should use allocator.
    EvalContext::Ptr ctxt_ = std::make_unique<EvalContext>(domain::EvalEventType::ExecMsg, msg);
    if (!strat)
        LOG_WARN("No strategy found for " << LOG_VAR(msg));
        return false;
    return strat->evaluate(ctxt_); // TODO Strategy::evaluate to return ReturnType
}
bool StrategyEngine::operator() (const FIX8::FIX44::NewOrderSingle* msg) const
{
    //TODO Make ExecutionMessage
    const StrategyPtr strat = getStrategyByMessage(msg);
    // should use allocator.
    EvalContext::Ptr ctxt_ = std::make_unique<EvalContext>(domain::EvalEventType::ExecMsg, msg);
    if (!strat)
        LOG_WARN("No strategy found for " << LOG_VAR(msg));
        return false;
    return strat->evaluate(ctxt_); // TODO Strategy::evaluate to return ReturnType
}


}


