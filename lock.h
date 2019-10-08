#ifndef __LOCK_H__
#define __LOCK_H__

#include <mutex>

// Wrapper de mutex. Lockea en el constructor. Unlockea en el destructor.
class Lock {
    private:
        std::mutex &m;

        Lock(const Lock&) = delete;
        Lock& operator=(const Lock&) = delete;
        Lock(Lock&&) = delete;
        Lock& operator=(Lock&&) = delete;

    public:
        explicit Lock(std::mutex &m);
        ~Lock();
};

#endif
