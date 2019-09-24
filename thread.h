#ifndef __THREAD_H__
#define __THREAD_H_

#include <stdio.h>
#include <thread>

class Thread {
    private:
    std::thread thread;

    protected:
    const size_t tnumber;
 
    public:
    Thread(size_t tnumber);
    void start();
    void join();
    virtual void run() = 0; 
    virtual ~Thread();
                            
    Thread(const Thread&) = delete;
    Thread& operator=(const Thread&) = delete;
    Thread& operator=(Thread&& other);
    Thread(Thread&& other);
};

#endif
