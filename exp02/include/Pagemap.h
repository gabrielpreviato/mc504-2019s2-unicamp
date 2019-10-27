// Copyright 2019 Gabriel Previato @ UNICAMP.
//
// All components of this repository are licensed under the MIT License.
// See LICENSE.txt for details.

#ifndef PAGEMAP_H_
#define PAGEMAP_H_
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

#include "Maps.h"


class Pagemap {
 private:
    int _pid;
    std::string _pagemap_file;
    int _file_stream;

    Maps _maps;
    std::vector<std::pair<uint64_t, uint64_t>> _present_pages;
    std::vector<std::pair<uint64_t, bool>> _missed_pages;

 public:
    explicit Pagemap(int pid);

    void read_pagemap_file();
    void print_pagemap();
};

#endif  // PAGEMAP_H_
