#ifndef TESTENVIRONMENT_H
#define TESTENVIRONMENT_H
// std
#include <queue>
#include <memory>
#include <chrono>
#include <thread>

// fix 8
#include <fix8/f8includes.hpp>
#include <FIX44_types.hpp>
#include <FIX44_router.hpp>
#include <FIX44_classes.hpp>

//test
#include "FixServer.h"

//utils/domain
#include <include.hpp>
#include <Enums.h>

// engine
#include <ConfigManager.h>
#include "SessionImpl.h"

/* Tokenizing a string */
std::vector<std::string> tokenizer( const std::string& p_pcstStr, char delim )  {
    std::vector<std::string> tokens;
    std::stringstream   mySstream( p_pcstStr );
    std::string         temp;

    while( getline( mySstream, temp, delim ) ) {
        tokens.push_back( temp );
    }

    return tokens;
} 
using namespace domain;

namespace testfwk
{


class EnvMessage
{
    FIX8::Message*                  _msg;
    GETSET(std::string,             data)
    GETSET(domain::EnvSource,       envSource)
    GETSET(domain::EnvMessageType,  type)
public:
    using Ptr = std::shared_ptr<EnvMessage>;
    EnvMessage(const std::string& data_)
    :   _data(data_)
    {
        // TODO: remove from constructor.
        thread_local std::vector<std::string> fields; fields.reserve(15);
        fields.clear();
        fields = tokenizer(_data, ' ');
        // source_system
        _envSource = str2enum<EnvSource>(fields[0].c_str());
        if (_envSource == EnvSource::UnknownEnvSource)
        {
            LOG_ERROR("Invalid message source! " << LOG_VAR(fields[0]));
        }
        _type = str2enum<EnvMessageType>(fields[1].c_str());
        switch(_type)
        {
            case(EnvMessageType::ExecutionReport):
            {
                _msg = new FIX44::ExecutionReport();
            }
            case(EnvMessageType::NewOrderSingle):
            {
                _msg = new FIX44::NewOrderSingle();
            }
            case(EnvMessageType::MarketData):
            {
                assert(false && "MarketData events have not yet been implemented");
            }
            case(EnvMessageType::UnknownEnvMessageType):
            {
                LOG_ERROR("UnknownEnvMessageType!");
            }
        }
        // msg type
        _type = str2enum<EnvMessageType>(fields[1].c_str()); 
        thread_local std::vector<std::string> name_vals; name_vals.reserve(2);
        name_vals.clear();
        // TODO: move this to seperate method to produce a struct
        // so that we may reuse it on env assertions.
        for (size_t i(2); i < fields.size(); i++)
        {
            LOG_DEBUG("Parsing field: " << LOG_VAR(fields[i]) << LOG_VAR(i));
            if (fields[i].find("=") == std::string::npos)
                LOG_ERROR("Invalid field supplied in test message: " << fields[i]);
                //error here invalid field in message
            name_vals = tokenizer(fields[i], '=');
            auto name = domain::str2enum<EnvMessageField >(name_vals[0].c_str());
            switch(name)
            {
                case(EnvMessageField::ExecType):
                {
                    *_msg << new FIX44::ExecType();
                }
                case(EnvMessageField::ExDestination):
                {
                    *_msg << new FIX44::ExDestination(name_vals[1]);
                }
                case(EnvMessageField::OrderQty):
                {
                    *_msg << new FIX44::OrderQty(std::stoi(name_vals[1]));
                }
                case(EnvMessageField::Price):
                {
                    *_msg << new FIX44::Price(std::stod(name_vals[1]));
                }
                case(EnvMessageField::Symbol):
                {
                    *_msg << new FIX44::Symbol(name_vals[1]);
                }
                case(EnvMessageField::TimeInForce):
                {
                    *_msg << new FIX44::TimeInForce(name_vals[1]);
                }
                default:
                {
                    LOG_ERROR("Unknown field: " << fields[i]);
                }
            }
            name_vals.clear();
        }
    }
    const FIX8::Message* getmessage() { return _msg; }
};

// specialization for comparing different types
template<typename T>
bool compareValues(std::string& msg_, T exp_, T rec_)
{
    if (exp_ == rec_)
        return true;
    msg_ = "expected values are not equal: received=" + rec_ + ", expected=" + exp_;
    return false;
}
template<>
bool compareValues(std::string& msg_, double exp_, double rec_)
{
    if (utils::almost_equal(exp_, rec_))
        return true;
    msg_ = "expected values are not equal: received=" + std::to_string(rec_) + ", expected=" + std::to_string(exp_);
    return false;
}

class TestEnvironment
{

public:
    using TestServerInstance = FIX8::SessionInstance<TestFixServer>;
    using TestServerSession= FIX8::ServerSession<TestFixServer>;
private:
    GETSET(unsigned,                                      next_send)
    GETSET(unsigned,                                      next_receive)
    GETSET(FIX8::tty_save_state,                          save_tty)
    f8_atomic<bool>                                       _term_received;

    std::shared_ptr<std::queue<const FIX8::Message*>>     _receivedMsgs;
    std::string                                           _client_config_file;
    std::string                                           _server_config_file;

    TestFixServer*                                        _server_session;
    TestServerInstance*                                   _server_instance;
    std::unique_ptr<engine::SessionImpl>                  _client_session;
    std::unique_ptr<TestServerSession>                    _session;
    std::thread                                           _server_thread;

    cfg::ConfigManager::Ptr                               _configManager;


public:
    // TODO extract common between Test and Real into factory so that we can change config file locations.
    TestEnvironment(cfg::ConfigManager::Ptr configManager_)
    :   _next_send(0)
    ,   _next_receive(0)
    ,   _save_tty(0)
    ,   _term_received(false)
    ,   _receivedMsgs()
    ,   _client_config_file("/home/rory/dev/algomon/test/myfix_client.xml")
    ,   _server_config_file("/home/rory/dev/algomon/test/myfix_server.xml")
    ,   _session(std::unique_ptr<TestServerSession>(new TestServerSession(FIX44::ctx(), _server_config_file, "TEST_SERVER")))
    ,   _configManager()
    {
        const FIX8::SessionID my_session("TEST_SESSION");
        // TODO call server_process in seperate thread.
        //initalise_server_process(_session.get());
        _server_thread = std::thread(&TestEnvironment::server_process, this, _session.get());

        // TODO poll _server_instance for activation info. Then start client
        std::unique_ptr<FIX8::ClientSessionBase> mc(new ClientSession<engine::SessionImpl>(
                   FIX44::ctx(), _client_config_file, "TEST_SESSION"));
        //_server_thread.join();
        mc->session_ptr()->control() |= Session::printnohb;
        // TODO wait_complete method on client to kill server thread.
        // TODO call client_process in seperate thread and join in wait_tests_complete method.
        mc->start(false, _next_send, _next_receive, mc->session_ptr()->get_login_parameters()._davi());
    }

    template<typename T>
    bool checkField(const FIX8::Message* expMsg_, const FIX8::Message* rvdMsg_, std::string& reason_)
    {
        T valRvd, expVal;
        if (!expMsg_->get(expVal))
        {
            reason_ = "Missing mandatory field on received message";
            LOG_ERROR(reason_);
            return false;
        }
        if (!rvdMsg_->get(valRvd))
        {
            reason_ = "Missing mandatory field on expected message";
            LOG_ERROR(reason_);
            return false;
        }
        else
        {
            return compareValues(reason_, expVal.get(), valRvd.get());
        }
    }

    bool operator>>(const std::string& msg_)
    {
        auto start = std::chrono::high_resolution_clock::now();
        while(_receivedMsgs->empty()) 
        {
            auto elapsed = std::chrono::high_resolution_clock::now() - start;
            if (elapsed.count() > 100)
            {
                LOG_ERROR("Timed out waiting for " LOG_VAR(msg_));
                return false;
            }
        }
        const FIX8::Message* msg = _receivedMsgs->front();
        auto expectedMessage = EnvMessage(msg_);
        const FIX8::Message* exp = expectedMessage.getmessage();
        std::string failReason;
        if (!checkField<FIX44::MsgType>(exp, msg, failReason))
            return false;
        if (!checkField<FIX44::Price>(exp, msg, failReason))
            return false;
        if (!checkField<FIX44::Symbol>(exp, msg, failReason))
            return false;
        if (!checkField<FIX44::ExDestination>(exp, msg, failReason))
            return false;
        if (!checkField<FIX44::OrderQty>(exp, msg, failReason))
            return false;
        if (!checkField<FIX44::OrderQty>(exp, msg, failReason))
            return false;
        return true;
    }

    EnvMessage operator<<(const std::string& msg_)
    {
        auto msg = std::make_shared<EnvMessage>(msg_);
        switch(msg->getenvSource())
        {
            case(EnvSource::DOWNSTREAM):
            {
                switch(msg->gettype())
                {
                    case(EnvMessageType::NewOrderSingle):
                    {
                        LOG_ERROR("Invalid " << LOG_VAR(msg->gettype()) << " for " << msg->getenvSource());
                        //_session->sendOrderSingle(static_cast<const FIX44::NewOrderSingle*>(msg->getmessage())); 
                        break;
                    }
                    case(EnvMessageType::ExecutionReport):  
                    {
                        _server_session->sendExecutionReport(static_cast<const FIX44::ExecutionReport*>(msg->getmessage()));
                        break;
                    }
                    case(EnvMessageType::MarketData):
                    {
                        _server_session->sendMarketData(msg); // TODO this should be on the _client instead
                        break;
                    }
                    case(EnvMessageType::UnknownEnvMessageType):
                    {
                        LOG_ERROR("UnknownEnvMessageType!");
                        return EnvMessage(msg_);
                    }
                }
                break;
            }
            case(EnvSource::UPSTREAM):
            {
                switch(msg->gettype())
                {
                    case(EnvMessageType::NewOrderSingle):
                    {
                        _client_session->getengine()(dynamic_cast<const FIX44::NewOrderSingle*>(msg->getmessage()));
                        break;
                    }
                    case(EnvMessageType::ExecutionReport):
                    {
                        _client_session->getengine()(dynamic_cast<const FIX44::ExecutionReport*>(msg->getmessage()));
                        break;
                    }
                    case(EnvMessageType::MarketData):
                    {
                        LOG_ERROR("Invalid " << LOG_VAR(msg->gettype()) << " for " << msg->getenvSource() );
                        return EnvMessage(msg_);
                    }
                    default:
                    {
                        LOG_ERROR("Unknown msgtype!");
                        return EnvMessage(msg_);
                    }
                }
                break;
            }
            case(EnvSource::UnknownEnvSource):
            {
                LOG_ERROR("Invalid EnvSource supplied!");
                return EnvMessage(msg_);
            }
        }
        return EnvMessage(msg_);
    }
private:
    void initalise_server_process(FIX8::ServerSession<TestFixServer>* srv);
    void server_process(FIX8::ServerSession<TestFixServer> *srv);

};

} // testfwk
#endif
