// Copyright 2019 Gabriel Previato @ UNICAMP.
//
// All components of this repository are licensed under the MIT License.
// See LICENSE.txt for details.

#ifndef EXP01_INCLUDE_MAPS_H_
#define EXP01_INCLUDE_MAPS_H_
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>


class Maps {
 private:
    int _pid;  
    // char _maps_file[BUFSIZ];
    std::string _maps_file; 
    std::vector<std::string> _maps_virtual_pages;

 public:
    Maps(int pid) : _pid(pid) {}
    
    void read_maps_file();
    void parse_maps_file();
    void print_maps();
};

#endif  // EXP01_INCLUDE_MAPS_H_
