#ifndef __THREAD_H__
#define __THREAD_H__

#include <stdio.h>
#include <thread>

// Crea un thread al construirse y lo lanza con el método run
class Thread {
    private:
    std::thread thread;

    protected:
    const size_t tnumber;
 
    public:
    explicit Thread(size_t tnumber);
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
