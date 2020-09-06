#include "TestEnvironment.h"
#include "logger.h"
#include "SessionImpl.h"

namespace testfwk
{

void TestEnvironment::initalise_server_process(TestServerSession* srv)
{

}
TestEnvironment::TestServerInstance* TestEnvironment::getTestServerInstancePtr(TestServerSession* srv)
{
    int scnt(0);
    std::string s = "FIXSERVER";
    char name[16];
    pthread_setname_np(pthread_self(), s.c_str()); // set the name (pthread_self() returns the pthread_t of the current thread)    
    pthread_getname_np(pthread_self(), &name[0], sizeof(name));   
    LOG_INFO(name << ": Initialising server process");
    return  dynamic_cast<TestServerInstance*>(srv->create_server_instance());

}

void TestEnvironment::server_process(TestServerSession* srv)
{

    std::string s = "FIXSERVER";
    char name[16];
    pthread_setname_np(pthread_self(), s.c_str()); // set the name (pthread_self() returns the pthread_t of the current thread)    
    pthread_getname_np(pthread_self(), &name[0], sizeof(name));   
    LOG_INFO(name << "Initialization of server process complete");
	const ProcessModel pm(srv->get_process_model(srv->_ses));
    LOG_INFO(name << "starting server session.");
	_server_instance->start(pm == pm_pipeline, _next_send, _next_receive);
	if (_server_session->get_connection()->is_secure())
		LOG_INFO(name << "Session is secure (SSL)");
    TimerEvent<FIX8::Session> sample_callback(static_cast<bool (FIX8::Session::*)()>(&TestFixServer::sample_scheduler_callback), true);
    _server_session->get_timer().schedule(sample_callback, 60000); // call sample_scheduler_callback every minute forever	
	if (pm != pm_pipeline)
		while (!_server_session->is_shutdown())
			FIX8::hypersleep<h_milliseconds>(100);
	LOG_INFO(name << "Session finished.");
	_server_instance->stop();
}

} // testfwk
