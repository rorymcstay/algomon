#ifndef LOGGER_H
#define LOGGER_H

#define BOOST_LOG_DYN_LINK 1 // necessary when linking the boost_log library dynamically

#include <boost/log/trivial.hpp>
#include <boost/log/sources/global_logger_storage.hpp>

// the logs are also written to LOGFILE
#define LOGFILE "algomon.log"

// just log messages with severity >= SEVERITY_THRESHOLD are written
#define SEVERITY_THRESHOLD logging::trivial::debug

// register a global logger
BOOST_LOG_GLOBAL_LOGGER(logger, boost::log::sources::severity_logger_mt<boost::log::trivial::severity_level>)

// just a helper macro used by the macros below - don't use it in your code
#define LOG(severity) BOOST_LOG_SEV(logger::get(),boost::log::trivial::severity)


// ===== log macros =====
#define LOG_TRACE(message)   LOG(trace) << message
#define LOG_DEBUG(message)   LOG(debug) << message
#define LOG_INFO(message)    LOG(info) << message
#define LOG_WARNING(message) LOG(warning) << message
#define LOG_ERROR(message)   LOG(error) << message
#define LOG_FATAL(message)   LOG(fatal) << message

#define PREP_LOCK_DEBUG()\
    static std::mutex io_mutex;\
    {\
        std::lock_guard<std::mutex> lk(io_mutex);\
    }

#define LOCK_DEBUG(message)\
    {\
         std::lock_guard<std::mutex> lk(io_mutex);\
         LOG(trace) << __FILE__<< ":" << __LINE__ << #message <<" got lock";\
    }


#endif


