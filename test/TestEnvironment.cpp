#include "TestEnvironment.h"
#include "logger.h"
#include "SessionImpl.h"

namespace testfwk
{


void TestEnvironment::server_process(FIX8::ServerSessionBase *srv)
{
    int scnt(0);
    std::unique_ptr<SessionInstanceBase> inst(srv->create_server_instance());
    _server_session = dynamic_cast<TestFixServer*>(inst->session_ptr());
	inst->session_ptr()->control() |= Session::print;
    _server_session->getRouter().setmessageQueue(_receivedMsgs);
	glout_info << "client(" << scnt << ") connection established.";
	const ProcessModel pm(srv->get_process_model(srv->_ses));
	inst->start(pm == pm_pipeline, _next_send, _next_receive);
	if (inst->session_ptr()->get_connection()->is_secure())
		LOG_INFO("Session is secure (SSL)");
    TimerEvent<FIX8::Session> sample_callback(static_cast<bool (FIX8::Session::*)()>(&TestFixServer::sample_scheduler_callback), true);
    inst->session_ptr()->get_timer().schedule(sample_callback, 60000); // call sample_scheduler_callback every minute forever	
	if (pm != pm_pipeline)
		while (!inst->session_ptr()->is_shutdown())
			FIX8::hypersleep<h_milliseconds>(100);
	LOG_INFO("Session(" << std::to_string(scnt) << ") finished.");
	inst->stop();
}

} // testfwk
