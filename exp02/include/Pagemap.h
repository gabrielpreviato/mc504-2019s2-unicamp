// Copyright 2019 Gabriel Previato @ UNICAMP.
//
// All components of this repository are licensed under the MIT License.
// See LICENSE.txt for details.

#ifndef EXP01_INCLUDE_PAGEMAP_H_
#define EXP01_INCLUDE_PAGEMAP_H_
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

#include "Maps.h"


class Pagemap {
 private:
    int _pid;  
    // char _maps_file[BUFSIZ];
    std::string _pagemap_file; 

    Maps _maps;

 public:
    Pagemap(int pid);

    void read_pagemap_file();
    void print_pagemap();
};

#endif  // EXP01_INCLUDE_PAGEMAP_H_
