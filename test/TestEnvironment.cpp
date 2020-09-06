#include "TestEnvironment.h"
#include "logger.h"

namespace testfwk
{


template<typename T>
void TestEnvironment::server_process(ServerSessionBase *srv)
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
    TimerEvent<FIX8::Session> sample_callback(static_cast<bool (FIX8::Session::*)()>(&T::sample_scheduler_callback), true);
    inst->session_ptr()->get_timer().schedule(sample_callback, 60000); // call sample_scheduler_callback every minute forever	
	if (pm != pm_pipeline)
		while (!inst->session_ptr()->is_shutdown())
			FIX8::hypersleep<h_milliseconds>(100);
	LOG_INFO("Session(" << std::to_string(scnt) << ") finished.");
	inst->stop();
}

FIX8::tty_save_state save_tty(0);
f8_atomic<bool> term_received(false);

template<typename T>
void TestEnvironment::client_process(ClientSessionBase *mc)
{
    T client(*mc->session_ptr(), 0, std::cout);
	LOG_INFO("Menu started. Press '?' for help...");
	char ch(0);
	client.get_tty().set_raw_mode();
	_save_tty = client.get_tty();
	while(!client.get_istr().get(ch).bad() && !mc->has_given_up() && !_term_received && ch != 0x3 && client.process(ch));
	// don't explicitly call mc->session_ptr()->stop() with reliable sessions
	// before checking if the session is already shutdown - the framework will generally do this for you
	if (!mc->session_ptr()->is_shutdown())
		mc->session_ptr()->stop();

	client.get_tty().unset_raw_mode();
}
}
