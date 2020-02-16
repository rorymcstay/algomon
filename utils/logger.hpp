namespace utils {

#define LOG(msg) \
    std::cout << __FILE__ << "(" << __LINE__ << "): " << msg << std::endl 


#define PREP_LOCK_DEBUG()\
    static std::mutex io_mutex;\
    {\
        std::lock_guard<std::mutex> lk(io_mutex);\
    }

#define LOCK_DEBUG(message)\
    {\
         std::lock_guard<std::mutex> lk(io_mutex);\
         std::cout << __FILE__<< ":" << __LINE__ << #message <<" got lock" << std::endl;\
    }
}
