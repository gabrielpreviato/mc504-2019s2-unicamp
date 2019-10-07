// Copyright 2019 Gabriel Previato @ UNICAMP.
//
// All components of this repository are licensed under the MIT License.
// See LICENSE.txt for details.

#ifndef EXP01_INCLUDE_PRIORITYQUEUE_H_
#define EXP01_INCLUDE_PRIORITYQUEUE_H_
#include <pthread.h>
#include <iostream>
#include <queue>
#include <vector>

#include "Bat.h"


class PriorityQueue {
 private:
    std::queue<Bat*> _queue;
    int _size_to_give_turn = 2;
    bool _run_flag = true;

    pthread_mutex_t* _arrive;
    pthread_mutex_t* _release;

    bool* _at_crossing = nullptr;
    bool* _arrived = nullptr;
    bool* _give_turn = nullptr;
    bool* _released = nullptr;

 public:
    void change_size_turn(int new_size);
    void stop_execution();
    void add_bat(Bat* bat);
    bool is_empty();
    void start();

    PriorityQueue(pthread_mutex_t* arrive, pthread_mutex_t* release,
                  bool* at_crossing, bool* arrived, bool* give_turn,
                  bool* released);

    static void* startThread(void* context) {
        ((PriorityQueue*)context)->start();
        return nullptr;
    }
};

#endif  // EXP01_INCLUDE_PRIORITYQUEUE_H_
