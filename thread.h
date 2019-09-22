#ifndef __THREAD_H__
#define __THREAD_H_

#include <thread>

class Thread {
    private:
        std::thread thread;
 
    public:
        Thread();
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
