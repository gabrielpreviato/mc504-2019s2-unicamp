// Copyright 2019 Gabriel Previato @ UNICAMP.
//
// All components of this repository are licensed under the MIT License.
// See LICENSE.txt for details.

#include "PriorityQueue.h"


void PriorityQueue::change_size_turn(int new_size) {
    _size_to_give_turn = new_size;
}

void PriorityQueue::stop_execution() {
    _run_flag = false;
}

void PriorityQueue::add_bat(Bat* bat) {
    _queue.push(bat);
}

bool PriorityQueue::is_empty() {
    return _queue.empty();
}

void PriorityQueue::start() {
    Bat* bat = nullptr;

    while (true) {
        // Lock arrive mutex
        pthread_mutex_lock(_arrive);

        if (!*_at_crossing) {
            // Test if end of execution was reached
            if (!_run_flag && _queue.empty()) {
                pthread_mutex_unlock(_arrive);
                break;
            }

            // Take first BAT from Queue
            bat = _queue.front();

            if (bat != nullptr) {
                // BAT arrives at the crossing
                std::cout << "BAT " << bat->bat_number << " " <<
                          char(bat->bat_line) << " chegou no cruzamento" << std::endl;

                *_at_crossing = true;
            }
        }

        // Gives turn only once if queue size is bigger than K
        if (_queue.size() > _size_to_give_turn &&
            !*_give_turn) {
            *_give_turn = true;
        } else if (*_give_turn) {
            *_give_turn = false;
        }

        // Set flags that tells that arrive check was finished
        *_arrived = true;

        // Unlock arrive mutex
        pthread_mutex_unlock(_arrive);

        // Lock release mutex
        pthread_mutex_lock(_release);

        if (*_released) {
            bat = _queue.front();

            if (bat != nullptr) {
                std::cout << "BAT " << bat->bat_number << " " <<
                          char(bat->bat_line) << " saiu do cruzamento" << std::endl;
                _queue.pop();
            }

            *_at_crossing = false;
            *_arrived = false;
            *_released = false;

            // Test if end of execution was reached
            if (!_run_flag && _queue.empty()) {
                pthread_mutex_unlock(_release);
                break;
            }
        }

        // Unlocks mutex
        pthread_mutex_unlock(_release);
    }
}

PriorityQueue::PriorityQueue(pthread_mutex_t* arrive, pthread_mutex_t* release,
                  bool* at_crossing,  bool* arrived, bool* give_turn,
                  bool* released)
                  : _arrive(arrive), _release(release),
                    _at_crossing(at_crossing),  _arrived(arrived),
                    _give_turn(give_turn), _released(released) {}
