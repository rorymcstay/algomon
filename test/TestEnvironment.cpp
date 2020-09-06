#include "TestEnvironment.h"
#include "logger.h"
#include "SessionImpl.h"

namespace testfwk
{

void TestEnvironment::initalise_server_process(TestServerSession* srv)
{

}

void TestEnvironment::server_process(TestServerSession* srv)
{
    int scnt(0);
    LOG_INFO("Initialising server process");
    _server_instance = dynamic_cast<TestServerInstance*>(srv->create_server_instance());
    _server_session = dynamic_cast<TestFixServer*>(_server_instance->session_ptr());
    _server_session->getRouter().setmessageQueue(_receivedMsgs);
	_server_instance->session_ptr()->control() |= Session::print;
	glout_info << "client(" << scnt << ") connection established.";
    LOG_INFO("Initialization of server process complete");
	const ProcessModel pm(srv->get_process_model(srv->_ses));
    LOG_INFO("starting server session.");
	_server_instance->start(pm == pm_pipeline, _next_send, _next_receive);
	if (_server_session->get_connection()->is_secure())
		LOG_INFO("Session is secure (SSL)");
    TimerEvent<FIX8::Session> sample_callback(static_cast<bool (FIX8::Session::*)()>(&TestFixServer::sample_scheduler_callback), true);
    _server_session->get_timer().schedule(sample_callback, 60000); // call sample_scheduler_callback every minute forever	
	if (pm != pm_pipeline)
		while (!_server_session->is_shutdown())
			FIX8::hypersleep<h_milliseconds>(100);
	LOG_INFO("Session finished.");
	_server_instance->stop();
}

} // testfwk
