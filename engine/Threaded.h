#ifndef THREADED_H 
#define THREADED_H

#include <thread>

namespace engine
{


class Threaded
{
private:
    std::thread _thread;


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
};

}

#endif
