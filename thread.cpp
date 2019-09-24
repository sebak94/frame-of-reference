#include "thread.h"
#include <thread>

Thread::Thread(size_t tnumber): tnumber(tnumber) {}

void Thread::start() {
    thread = std::thread(&Thread::run, this);
}

void Thread::join() {
    thread.join();
}

Thread::~Thread() {}

Thread::Thread(Thread&& other): tnumber(other.tnumber) {
    thread = std::move(other.thread);
}

Thread& Thread::operator=(Thread&& other) {
    thread = std::move(other.thread);
    return *this;
}
