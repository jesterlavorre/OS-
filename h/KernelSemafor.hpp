//
// Created by os on 6/1/22.
//

#ifndef PROJECT_BASE_V1_0_KERNELSEMAFOR_HPP
#define PROJECT_BASE_V1_0_KERNELSEMAFOR_HPP
#include "syscall_cpp.hpp"
#include "list.hpp"
#include "tcb.hpp"

class TCB;
class Semaphore;
class KernelSemafor{

public:
    KernelSemafor(int initValue = 1);
    static KernelSemafor* createKernelSemafor(int initValue);
    ~KernelSemafor();
    int wait();
    int signal();
    int getValue() { return val; }
    static List<Semaphore> sviSem;

    void block();
    void deblock();
    List<TCB> *blockedlist;

    friend class List<Semaphore>;
    friend class Semaphore;
    friend class Riscv;
private:
    int ret;
    int val;
    Semaphore *handleSem;

};

#endif //PROJECT_BASE_V1_0_KERNELSEMAFOR_HPP
