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

 public:
    void read_map_file();
};

#endif  // EXP01_INCLUDE_MAPS_H_
