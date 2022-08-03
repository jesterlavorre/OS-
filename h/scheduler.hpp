//
// Created by os on 4/26/22.
//

#ifndef PROJECT_BASE_V1_0_SCHEDULER_HPP
#define PROJECT_BASE_V1_0_SCHEDULER_HPP

#include "list.hpp"

class TCB;
class Scheduler{
private:
    static List<TCB> readyCoroutineQueue;
public:
    static TCB *get();

    static void put(TCB *tcb);
};

#endif //PROJECT_BASE_V1_0_SCHEDULER_HPP
