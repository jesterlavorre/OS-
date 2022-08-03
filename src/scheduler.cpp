//
// Created by os on 4/26/22.
//
#include "../h/scheduler.hpp"

List<TCB>Scheduler::readyCoroutineQueue;

TCB *Scheduler::get() {
    return readyCoroutineQueue.removeFirst();
}

void Scheduler::put(TCB *tcb) {
    readyCoroutineQueue.addLast(tcb);
}