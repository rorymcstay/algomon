#ifndef FIXSERVER_H
#define FIXSERVER_H
#include <fix8/f8includes.hpp>

#include <logger.h>
#include <include.hpp>

#include "FIX44_types.hpp"
#include "FIX44_router.hpp"
#include "FIX44_classes.hpp"



namespace testfwk
{
class EnvMessage;
using EnvMessagePtr = std::shared_ptr<EnvMessage>;

using namespace FIX8;

template<typename T>
static T getrandom(const T range=0)
{
   T target(random());
   return range ? target / (RAND_MAX / range + 1) : target;
}

class TestFixServer;

class TestServerRouter : public FIX8::FIX44::FIX44_Router
{
    GETSET(std::shared_ptr<std::queue<const FIX8::Message*>>,   messageQueue);
    TestFixServer&                                              _session;

public:
    TestServerRouter(FIX8::Session& session_);
    TestFixServer& getSession() {return _session;}


    virtual bool operator() (const FIX8::FIX44::NewOrderSingle *msg) const
    {
        _messageQueue->emplace(msg);
        return true;
    }
    virtual bool operator() (const FIX8::FIX44::ExecutionReport* msg) const
    {
        _messageQueue->emplace(msg);
        return true;
    }
};


class TestFixServer : public FIX8::Session
{
    TestServerRouter      _router;
    FIX8::FilePersister*  _persistence;
public:
    TestFixServer(const FIX8::F8MetaCntx& ctx, 
            const FIX8::sender_comp_id& sci,
            FIX8::Persister *persist=nullptr,
            FIX8::Logger *logger=nullptr, FIX8::Logger *plogger=nullptr) 
    :   Session(ctx, sci, persist, logger, plogger)
    ,   _router(*this) 
    {
        LOG_INFO("Made fix server!");

    }

    TestServerRouter& getRouter() {return _router;}

    bool handle_application(const unsigned seqnum, const FIX8::Message *&msg)
    {
        if (enforce(seqnum, msg))
            return false;
        // this is how you take ownership of the message from the framework
        if (!msg->process(_router)) // false means I have taken ownership of the message
            detach(msg);
        return true;
    }

    bool sample_scheduler_callback()
    {
        LOG_INFO("::sample_scheduler_callback Hello!");
        return true;
    }

    void state_change(const FIX8::States::SessionStates before, const FIX8::States::SessionStates after)
    {
	    LOG_INFO(get_session_state_string(before) << " => " << get_session_state_string(after));
    }

    bool sendMarketData(const EnvMessagePtr msg)
    {
        return true;
    }

    bool rejectOrderSingle(const FIX44::ExecutionReport* msg){ return true; };
    bool sendExecutionReport(const FIX44::ExecutionReport* msg){return true;};
    bool cancelOrderSingle(const FIX44::ExecutionReport* msg){return true;};
}; 

}
#endif
