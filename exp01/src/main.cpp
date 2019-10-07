// Copyright 2019 Gabriel Previato @ UNICAMP.
//
// All components of this repository are licensed under the MIT License.
// See LICENSE.txt for details.

#include <pthread.h>
#include <cctype>
#include <iostream>
#include <string>

#include "PriorityQueue.h"
#include "Bat.h"


int get_crossing_size(const bool* crossing) {
    int count = 0;

    if (crossing[0]) {
        count++;
    }
    if (crossing[1]) {
        count++;
    }
    if (crossing[2]) {
        count++;
    }
    if (crossing[3]) {
        count++;
    }

    return count;
}

std::string get_crossing_bat_string(const bool* crossing) {
    std::string ret;

    if (crossing[0]) {
        ret += "N";
    }
    if (crossing[1]) {
        ret += "E";
    }
    if (crossing[2]) {
        ret += "S";
    }
    if (crossing[3]) {
        ret += "W";
    }

    for (std::string::size_type i = 1; i < ret.size(); i += 2) {
        ret.insert(i, ",");
    }

    return ret;
}

pthread_mutex_t g_stdin_mutex = PTHREAD_MUTEX_INITIALIZER;
// String for non blocking stdin
std::string g_stdin_str;

void* get_stdin(void*) {
    while (true) {
        pthread_mutex_lock(&g_stdin_mutex);
        if (g_stdin_str[0] == 'q' && g_stdin_str.length() == 1) {
            break;
        }

        if (g_stdin_str.length() == 0) {
            std::string str;
            std::cin >> str;

            g_stdin_str += str;
        }

        pthread_mutex_unlock(&g_stdin_mutex);
    }

    pthread_mutex_unlock(&g_stdin_mutex);
    return nullptr;
}

int main() {
    // Creates mutex
    pthread_mutex_t arrive = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t release = PTHREAD_MUTEX_INITIALIZER;

    // Creates the queues
    bool crossing[4] = {false};
    bool arrived[4] = {false};
    bool give_turn[4] = {false};
    bool released[4] = {false};

    PriorityQueue north_queue = PriorityQueue(&arrive, &release, &crossing[0],
                                              &arrived[0], &give_turn[0], &released[0]);
    PriorityQueue east_queue = PriorityQueue(&arrive, &release, &crossing[1],
                                             &arrived[1], &give_turn[1], &released[1]);
    PriorityQueue south_queue = PriorityQueue(&arrive, &release, &crossing[2],
                                              &arrived[2], &give_turn[2], &released[2]);
    PriorityQueue west_queue = PriorityQueue(&arrive, &release, &crossing[3],
                                             &arrived[3], &give_turn[3], &released[3]);

    // Bat counts
    int bat_count = 1;

    // Starts threads
    pthread_t thread_north, thread_east, thread_south, thread_west;
    pthread_t stdin_thread;

    pthread_mutex_lock(&arrive);
    pthread_mutex_lock(&release);

    pthread_create(&thread_north, nullptr, &PriorityQueue::startThread, &north_queue);
    pthread_create(&thread_east, nullptr, &PriorityQueue::startThread, &east_queue);
    pthread_create(&thread_south, nullptr, &PriorityQueue::startThread, &south_queue);
    pthread_create(&thread_west, nullptr, &PriorityQueue::startThread, &west_queue);

    pthread_create(&stdin_thread, nullptr, &get_stdin, nullptr);

    // Main thread loop
    bool first_run = true;
    while (true) {
        // Gets the line (doesn't block other threads execution)
        pthread_mutex_lock(&g_stdin_mutex);
//        std::string &line = g_stdin_str;
//        g_stdin_str = "";
//        pthread_mutex_unlock(&g_stdin_mutex);

        // Locks mutex after first run
        if (!first_run) {
            pthread_mutex_lock(&arrive);
            pthread_mutex_lock(&release);
        }
        first_run = false;

        // Add the BATs from the line input to the respective Queue
        while (g_stdin_str.length() != 0) {
            // std::cout << g_stdin_str.length() << std::endl;
            // Checks for execution end
            if (g_stdin_str[0] == 'q' && north_queue.is_empty() && east_queue.is_empty() && south_queue.is_empty() && west_queue.is_empty()) {
                north_queue.stop_execution();
                east_queue.stop_execution();
                south_queue.stop_execution();
                west_queue.stop_execution();

                // Unlocks mutex
                pthread_mutex_unlock(&arrive);
                pthread_mutex_unlock(&release);
                break;
            }

            if (g_stdin_str[0] == 'q') {
                break;
            }

            // Checks for K change
            if (g_stdin_str[0] == 'K') {
                // Get intenger from input "K=< algum_inteiro_razoavel >"
                std::string int_string = g_stdin_str.substr(2);
                int new_K = std::stoi(int_string);

                // Change K for all queues
                north_queue.change_size_turn(new_K);
                east_queue.change_size_turn(new_K);
                south_queue.change_size_turn(new_K);
                west_queue.change_size_turn(new_K);

                // Unlocks mutex
                pthread_mutex_unlock(&arrive);
                pthread_mutex_unlock(&release);

                // Go back to the start of the loop
                continue;
            }
            if (g_stdin_str[0] != 'q' && g_stdin_str.length() != 0) {
                Bat* bat = new Bat(bat_count, char(toupper(g_stdin_str[0])));
                bat_count++;

                switch (g_stdin_str[0]) {
                case 'n':
                    north_queue.add_bat(bat);
                    break;
                case 'e':
                    east_queue.add_bat(bat);
                    break;
                case 's':
                    south_queue.add_bat(bat);
                    break;
                case 'w':
                    west_queue.add_bat(bat);
                    break;
                default:
                    break;
                }

                g_stdin_str.erase(0, 1);
            }

//            std::cout << "'" << bat_char << "'" << std::endl;
        }

        // Break outter loop
        if (g_stdin_str[0] == 'q' && north_queue.is_empty() && east_queue.is_empty() && south_queue.is_empty() && west_queue.is_empty()) {
            break;
        }
        pthread_mutex_unlock(&g_stdin_mutex);
//        std::cout << line << std::endl;

        // Unlock arrive mutex
        pthread_mutex_unlock(&arrive);

        int arrived_count = 0;
        // for (int i = 0; i < 4; i++) {
        //     if (arrived[i]) {
        //         arrived_count += 1;
        //     }
        // }
        while (true) {
            if (arrived[0] && arrived[1] && arrived[2] && arrived[3]) {
                break;
            }
        }
        arrived_count = 4;

        pthread_mutex_lock(&arrive);

        if (arrived_count > 0) {
            int impasse_size = get_crossing_size(crossing);

            if (impasse_size > 1) {
                std::string impasse = get_crossing_bat_string(crossing);
                std::string output = "Impasses: " + impasse + " sinalizando ";

                bool sent_command = false;
                if (crossing[0]) {
                    if (!give_turn[0]) {
                        released[0] = true;
                        released[1] = false;
                        released[2] = false;
                        released[3] = false;

                        sent_command = true;

                        output += "N para ir";
                    } else {
//                        give_turn[0] = false;
                    }
                }
                if (crossing[1] && !sent_command) {
                    if (!give_turn[1]) {
                        released[0] = false;
                        released[1] = true;
                        released[2] = false;
                        released[3] = false;

                        sent_command = true;

                        output += "E para ir";
                    } else {
//                        give_turn[1] = false;
                    }
                }
                if (crossing[2] && !sent_command) {
                    if (!give_turn[2]) {
                        released[0] = false;
                        released[1] = false;
                        released[2] = true;
                        released[3] = false;

                        sent_command = true;

                        output += "S para ir";
                    } else {
//                        give_turn[2] = false;
                    }
                }
                if (crossing[3] && !sent_command) {
                    if (!give_turn[3]) {
                        released[0] = false;
                        released[1] = false;
                        released[2] = false;
                        released[3] = true;

                        sent_command = true;

                        output += "W para ir";
                    } else {
//                        give_turn[3] = false;
                    }
                }

                // Print impasse output if a sent command was made
                if (sent_command) {
                    std::cout << output << std::endl;
                }
            } else if (impasse_size == 1)  {
                bool sent_command = false;
                if (crossing[0]) {
                    if (!give_turn[0]) {
                        released[0] = true;
                        released[1] = false;
                        released[2] = false;
                        released[3] = false;

                        sent_command = true;
                    } else {
//                        give_turn[0] = false;
                    }
                }
                if (crossing[1] && !sent_command) {
                    if (!give_turn[1]) {
                        released[0] = false;
                        released[1] = true;
                        released[2] = false;
                        released[3] = false;

                        sent_command = true;
                    } else {
//                        give_turn[1] = false;
                    }
                }
                if (crossing[2] && !sent_command) {
                    if (!give_turn[2]) {
                        released[0] = false;
                        released[1] = false;
                        released[2] = true;
                        released[3] = false;

                        sent_command = true;
                    } else {
//                        give_turn[2] = false;
                    }
                }
                if (crossing[3] && !sent_command) {
                    if (!give_turn[3]) {
                        released[0] = false;
                        released[1] = false;
                        released[2] = false;
                        released[3] = true;

                    } else {
//                        give_turn[3] = false;
                    }
                }
            }   // else {do nothing}
        }
        pthread_mutex_unlock(&arrive);
        pthread_mutex_unlock(&release);

        // Wait for release
        while (released[0] || released[1] || released[2] || released[3]) {}
    }

    // Join threads
    pthread_join(thread_north, nullptr);
    pthread_join(thread_east, nullptr);
    pthread_join(thread_south, nullptr);
    pthread_join(thread_west, nullptr);

    pthread_join(stdin_thread, nullptr);

    return 0;
}
