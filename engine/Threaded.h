#ifndef THREADED_H 
#define THREADED_H

#include <thread>
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
    void initalise()
    {
        _thread = std::thread( &Threaded::run, this);
    }

    void join()
    {
        _thread.join();
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
