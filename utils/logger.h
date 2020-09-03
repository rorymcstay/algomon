#ifndef LOGGER_H
#define LOGGER_H
#include <pthread.h>

#include <string.h>

#define BOOST_LOG_DYN_LINK 1 // necessary when linking the boost_log library dynamically

#include <boost/log/trivial.hpp>
#include <boost/log/sources/global_logger_storage.hpp>

// the logs are also written to LOGFILE
#define LOGFILE "algomon.log"

// just log messages with severity >= SEVERITY_THRESHOLD are written
#define SEVERITY_THRESHOLD logging::trivial::debug

// register a global logger
BOOST_LOG_GLOBAL_LOGGER(logger, boost::log::sources::severity_logger_mt<boost::log::trivial::severity_level>)


#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
// just a helper macro used by the macros below - don't use it in your code
#define LOG(severity) BOOST_LOG_SEV(logger::get(),boost::log::trivial::severity) 

inline std::string getThreadName()
{
    char* ret = nullptr;
    pthread_getname_np(pthread_self(), ret, 15);
    if( ret)
        return ret;
    else
        return "";
}
#define LOG_POST_FIX  " |" << __FILENAME__ << ":" << __LINE__
// ===== log macros =====
#define LOG_TRACE(message)   LOG(trace) << message  << LOG_POST_FIX
#define LOG_DEBUG(message)   LOG(debug) << message << LOG_POST_FIX
#define LOG_INFO(message)    LOG(info) << message << LOG_POST_FIX
#define LOG_WARNING(message) LOG(warning) << message << LOG_POST_FIX
#define LOG_WARN(message)    LOG_WARNING(message)
#define LOG_ERROR(message)   LOG(error) << message << LOG_POST_FIX
#define LOG_FATAL(message)   LOG(fatal) << message << LOG_POST_FIX

#define PREP_LOCK_DEBUG()\
    static std::mutex io_mutex;\
    {\
        std::lock_guard<std::mutex> lk(io_mutex);\
    }

#define LOCK_DEBUG(message)\
    {\
         std::lock_guard<std::mutex> lk(io_mutex);\
         LOG(trace) << __FILENAME__<< ":" << __LINE__ << #message <<" got lock";\
    }
#define LOG_VAR(var) #var"='" << var  << "', "

#endif


