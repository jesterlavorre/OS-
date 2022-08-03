//
// Created by os on 4/26/22.
//
#include "../h/printing.hpp"
#include "../h/scheduler.hpp"
#include "../h/riscv.hpp"

TCB *TCB::running = nullptr;
uint64 TCB::timeSliceCounter = 0;

TCB::TCB(Body body, uint64 timeSlice, void *data) : body(body),
stack(/*body != nullptr ?*/ new uint64[STACK_SIZE] /*: nullptr*/),
context({(uint64) &threadWrapper,
         /*stack != nullptr ?*/ (uint64) &stack[STACK_SIZE] /*: 0 */}),
timeSlice(timeSlice),
finished(false), data(data){

    if (body != nullptr) {
        Scheduler::put(this);
    }
    handleThread = nullptr;
}

TCB *TCB::createThread(Body body, void *data) { return new TCB(body, TIME_SLICE, data); }

void TCB::yield() {
    //uint64 sstatus = Riscv::r_sstatus();
    __asm__ volatile ("ecall");
   // Riscv::w_sstatus(sstatus);
}

void TCB::dispatch() {
    TCB *old = running;
    //uint64 sstatus = Riscv::r_sstatus();
    if (!old->isFinished()) { Scheduler::put(old); }
    TCB *pomoc = Scheduler::get();
    running = pomoc;
   // Riscv::w_sstatus(sstatus);
    //Kapetanov dnevnik, nek sisa kurac ovo sto gubi sstatus
    TCB::contextSwitch(&old->context, &running->context);
}

void TCB::threadWrapper() {
    Riscv::popSppSpie();
    if(running->body!= nullptr && running->data != nullptr){
        running->body(running->data);
    }
    if(running->body!= nullptr && running->data == nullptr){
        running->body(nullptr);
    }
    if(running->handleThread!= nullptr) {
        running->handleThread->run();
    }
    thread_exit();
//    running->setFinished(true);
//    thread_dispatch();
}
