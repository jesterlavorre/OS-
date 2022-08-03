//
// Created by os on 6/1/22.
//
#include "../h/KernelSemafor.hpp"
#include "../h/scheduler.hpp"

List<Semaphore> KernelSemafor::sviSem;

KernelSemafor::KernelSemafor(int initValue) {

    val = initValue;
    blockedlist = new List<TCB>;
    //handleSem = sem;
    //sviSem.addFirst(sem);

}
KernelSemafor *KernelSemafor::createKernelSemafor(int initValue) {

    return new KernelSemafor(initValue);

}
KernelSemafor::~KernelSemafor() {

    delete blockedlist;
    __asm__ volatile("csrw sscratch, %0" : : "r" (0));
}
int KernelSemafor::wait() {
    ret = 1;
        if (--val<0) {
            ret = 0;
            block();
        }
        if(ret == 0)
            TCB::dispatch();
    return ret;

}
int KernelSemafor::signal() {
    ret = 1;
    if(++val<=0) {
        deblock();
        ret = 0;
    }
    return ret;
}
void KernelSemafor::block() {
        TCB::running->setFinished(true);
        blockedlist->addLast(TCB::running);
}
void KernelSemafor::deblock() {

    TCB *tcb = blockedlist->removeFirst();
    if(tcb != nullptr) {
        tcb->setFinished(false);
        Scheduler::put(tcb);
    }
}