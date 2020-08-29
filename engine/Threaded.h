#ifndef THREADED_H 
#define THREADED_H

#include <thread>
#include <pthread.h>
#include <include.hpp>
#include <mutex>

namespace engine
{


class Threaded
{
private:
    std::thread                 _thread;
    std::shared_ptr<Threaded>   _linkedThread;
    std::mutex                  _lock;
    bool                        _paused;
    GETSET(int,                 latestTime);

    virtual void run() = 0;
public:
    void initalise(const std::string& name)
    {
        _thread = std::thread( &Threaded::run, this);
        
        pthread_setname_np(pthread_self(), name.c_str());
    }

    void join()
    {
        _thread.join();
    }

    void setlinkedThread(std::shared_ptr<Threaded> pub_)
    {
        _linkedThread = pub_;
    }
    const std::shared_ptr<Threaded>& linkedThread()
    {
        return _linkedThread;
    }
    void pause()
    {
        std::lock_guard<std::mutex> lk1(_lock, std::adopt_lock);
        if (_linkedThread)
        {
            _linkedThread->pause();
        }
        _paused = true; 
    }

    bool isPaused()
    {
        if (_linkedThread)
        {
            return _linkedThread->isPaused();
        }
        else
        {
            return _paused;
        }
    }
};

}

#endif
