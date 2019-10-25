#include "Pagemap.h"
#include <fstream>
#include <cstdio>
#include <unistd.h>

#define PAGE_SIZE 0x1000

    
Pagemap::Pagemap(int pid) : _pid(pid), _maps(pid), 
                            _file_stream(fopen((std::string("/proc/") + std::to_string(_pid) + std::string("/pagemap")).c_str(), 'r'))
                            {}

void Pagemap::read_pagemap_file() {
    std::cout << "Before reading maps." << std::endl;

    _maps.read_maps_file();
    _maps.parse_maps_file();

    std::cout << "Done reading maps." << std::endl;

    
    for (auto range : _maps._maps_virtual_ranges) {
        for (uint64_t i = range.first; i < range.second; i += PAGE_SIZE) {
            uint64_t page_index = i / PAGE_SIZE;
            std::string pagemap(std::istreambuf_iterator<char>(_file_stream) + page_index,
                                std::istreambuf_iterator<char>(_file_stream) + page_index + 1);
        }
    }
    return;
}

void Pagemap::print_pagemap() {
    _maps.print_maps();
    // std::cout << _pagemap_file << std::endl;
    
    return;
}