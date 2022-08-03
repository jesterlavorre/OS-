//
// Created by os on 5/17/22.
//
#include "../h/syscall_c.hpp"

#include "../h/printing.hpp"
#include "../h/riscv.hpp"

void* mem_alloc (size_t size){

    uint64 arg = 69;
    uint64 broj = 1;
    // ucitas u arg parametar, u a0 stavis broj poziva, pa u a1 stavis sta si prvo ucitao iz a0
    __asm__ volatile("mv %0, a0" : "=r" (arg));// ovako se nesto ucitava u arg
    __asm__ volatile("mv a0, %0" : : "r" (broj));// ovako se nesto upisuje u a0 iz broj
    __asm__ volatile("mv a1, %0" : : "r" (arg));

    __asm__ volatile ("ecall");

    void* ret;
    __asm__ volatile("mv %0, a0" : "=r" (ret));

    return ret;

}
int mem_free (void* addr){

    void* arg;
    int broj = 2;
    // ucitas u arg parametar, u a0 stavis broj poziva, pa u a1 stavis sta si prvo ucitao iz a0
    __asm__ volatile("mv %0, a0" : "=r" (arg));// ovako se nesto ucitava u arg
    __asm__ volatile("mv a0, %0" : : "r" (broj));// ovako se nesto upisuje u a0 iz broj
    __asm__ volatile("mv a1, %0" : : "r" (arg));

    __asm__ volatile ("ecall");

    int ret;
    __asm__ volatile("mv %0, a0" : "=r" (ret));

    return ret;

}
int thread_create (thread_t* handle, void(*start_routine)(void*), void* arg){

    thread_t *arg1 ;
    TCB::Body arg2 ;
    void* arg3 ;
    //void* stack_space =
    uint64 broj = 11;

    __asm__ volatile("mv %0, a0" : "=r" (arg1));
    __asm__ volatile("mv %0, a1" : "=r" (arg2));
    __asm__ volatile("mv %0, a2" : "=r" (arg3));

    //char* proba = (char*)arg1 - 80;

    __asm__ volatile("mv a0, %0" : : "r" (broj));// ovako se nesto upisuje u a0 iz broj
    __asm__ volatile("mv a1, %0" : : "r" (arg1));
    __asm__ volatile("mv a6, %0" : : "r" (arg2));
    __asm__ volatile("mv a7, %0" : : "r" (arg3));

    __asm__ volatile ("ecall");


   //*handle = TCB::createThread(start_routine);
    /*Dnevnik kapetana, nek mi sisa kurac ovo prosledjuvanje sto dobro ne radi*/
   return 0;
}
void thread_dispatch (){

    uint64 broj = 13;

    __asm__ volatile("mv a0, %0" : : "r" (broj));
    //uint64 sstatus = Riscv::r_sstatus();
    __asm__ volatile ("ecall");
    //Riscv::w_sstatus(sstatus);
}
int thread_exit (){

    uint64 broj = 12;

    __asm__ volatile("mv a0, %0" : : "r" (broj));
    //uint64 sstatus = Riscv::r_sstatus();
    __asm__ volatile ("ecall");
    //Riscv::w_sstatus(sstatus);

    return 1;

}
int sem_open (sem_t* handle, unsigned init){ // 0x21

    uint64 broj = 21;
    sem_t *sem;
    uint64 ini;
    __asm__ volatile("mv %0, a0" : "=r" (sem));
    __asm__ volatile("mv %0, a1" : "=r" (ini));

    __asm__ volatile("mv a0, %0" : : "r" (broj));// ovako se nesto upisuje u a0 iz broj
    __asm__ volatile("mv a1, %0" : : "r" (sem));
    __asm__ volatile("mv a2, %0" : : "r" (ini));

    __asm__ volatile("ecall");

    return 0;
}
int sem_close (sem_t handle) { //0x22

    uint64 broj = 22;
    sem_t sem;
    __asm__ volatile("mv %0, a0" : "=r" (sem));

    __asm__ volatile("mv a0, %0" : : "r" (broj));// ovako se nesto upisuje u a0 iz broj
    __asm__ volatile("mv a1, %0" : : "r" (sem));

    __asm__ volatile("ecall");

    int ret;
    __asm__ volatile("mv %0, a0" : "=r" (ret));

    return ret;
}
int sem_wait (sem_t id) { // 0x23

    uint64 broj = 23;
    sem_t idet;

    __asm__ volatile("mv %0, a0" : "=r" (idet));

    __asm__ volatile("mv a0, %0" : : "r" (broj));// ovako se nesto upisuje u a0 iz broj
    __asm__ volatile("mv a1, %0" : : "r" (idet));

    __asm__ volatile("ecall");

    int ret;
    __asm__ volatile("mv %0, a0" : "=r" (ret));

    return ret;
}
int sem_signal (sem_t id) { // 0x24

    uint64 broj = 24;
    sem_t idet;

    __asm__ volatile("mv %0, a0" : "=r" (idet));

    __asm__ volatile("mv a0, %0" : : "r" (broj));// ovako se nesto upisuje u a0 iz broj
    __asm__ volatile("mv a1, %0" : : "r" (idet));

    __asm__ volatile("ecall");

    int ret;
    __asm__ volatile("mv %0, a0" : "=r" (ret));

    return ret;
}
char getc (){ //0x41

    uint64 broj = 41;
    __asm__ volatile("mv a0, %0" : : "r" (broj));
    __asm__ volatile("ecall");

    char ret;
    __asm__ volatile("mv %0, a0" : "=r" (ret));
    return ret;
}
void putc (char c){ //0x42

    uint64 broj = 42;
    char kara;

    __asm__ volatile("mv %0, a0" : "=r" (kara));

    __asm__ volatile("mv a0, %0" : : "r" (broj));
    __asm__ volatile("mv a1, %0" : : "r" (kara));
    __asm__ volatile("ecall");

}