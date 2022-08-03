//
// Created by os on 5/17/22.
//

#ifndef PROJECT_BASE_V1_0_SYSCALL_CPP_HPP
#define PROJECT_BASE_V1_0_SYSCALL_CPP_HPP

#include "syscall_c.hpp"
#include "tcb.hpp"

class KernelSemafor;
typedef KernelSemafor* sem_t;

class TCB;
typedef TCB* thread_t;

class Thread {
public:
    Thread (void (*body)(void*), void* arg);
    virtual ~Thread ();
    int start ();
    static void dispatch ();
    static int sleep (time_t);
protected:
    Thread ();
    virtual void run () {}
private:
    thread_t myHandle;
    friend class TCB;
};
class Semaphore {
public:
    Semaphore (unsigned init = 1);
    virtual ~Semaphore ();
    int wait ();
    int signal ();

private:
    sem_t myHandle;
};
//class PeriodicThread : public Thread {
//protected:
//    PeriodicThread (time_t period);
//    virtual void periodicActivation () {}
//};
class Console {
public:
    static char getc ();
    static void putc (char c);
};

#endif //PROJECT_BASE_V1_0_SYSCALL_CPP_HPP
