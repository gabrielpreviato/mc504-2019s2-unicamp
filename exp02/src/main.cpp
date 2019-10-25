// Copyright 2019 Gabriel Previato @ UNICAMP.
//
// All components of this repository are licensed under the MIT License.
// See LICENSE.txt for details.

#include <pthread.h>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <string>

#include "Maps.h"
#include "Pagemap.h"


int main(int argc, char** argv) {
    if (argc != 2) {
        return 1;
    }

    std::cout << "PID: " << argv[1] << std::endl;
    int pid = atoi(argv[1]);

    Pagemap pagemap = Pagemap(pid);
    pagemap.read_pagemap_file();
    pagemap.print_pagemap();

    return 0;
}