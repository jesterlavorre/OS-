//
// Created by os on 5/18/22.
//
#include "../h/syscall_cpp.hpp"
#include "../h/scheduler.hpp"

Thread::Thread(void (*body)(void *), void *arg) {
    thread_create(&myHandle, body, arg);
    myHandle->handleThread = this;
}
Thread::Thread() {
    thread_create(&myHandle, nullptr, nullptr);
    myHandle->handleThread = this;
    //Kapetanov dnevnik, ovo mora jer ne znas kako da dovatis run
}
void Thread::dispatch() {
    thread_dispatch();
}
Thread::~Thread() noexcept {
    delete myHandle;
}

int Thread::start() {

   // if (myHandle->body != nullptr) {
        Scheduler::put(myHandle);
    //}
    return 1;
}
Semaphore::Semaphore(unsigned int init) {

    sem_open(&myHandle, init);
    myHandle->handleSem = this;
    myHandle->sviSem.addFirst(this);
}
Semaphore::~Semaphore() {
    sem_close(myHandle);
}

int Semaphore::wait() {
    return sem_wait(myHandle);
}

int Semaphore::signal() {
    return sem_signal(myHandle);
}

char Console::getc() {
    return ::getc();
}

void Console::putc(char c) {
    ::putc(c);
}
