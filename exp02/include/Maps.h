// Copyright 2019 Gabriel Previato @ UNICAMP.
//
// All components of this repository are licensed under the MIT License.
// See LICENSE.txt for details.

#ifndef MAPS_H_
#define MAPS_H_
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <utility>


class Maps {
 private:
    int _pid;
    std::string _maps_file;
    std::vector<std::string> _maps_virtual_pages;

 public:
    std::vector<std::pair<uint64_t, uint64_t>> _maps_virtual_ranges;

    explicit Maps(int pid) : _pid(pid) {}

    void read_maps_file();
    void parse_maps_file();
    void print_maps();
};

#endif  // MAPS_H_
