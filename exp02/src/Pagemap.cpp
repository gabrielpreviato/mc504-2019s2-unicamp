#include "Pagemap.h"
#include <fstream>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>

#define PAGE_SIZE 0x1000


Pagemap::Pagemap(int pid) : _pid(pid), _maps(pid), 
                            _file_stream(open((std::string("/proc/") + std::to_string(_pid) + std::string("/pagemap")).c_str(), O_RDONLY))
                            {}

void Pagemap::read_pagemap_file() {
    std::cout << "Before reading maps." << std::endl;

    _maps.read_maps_file();
    _maps.parse_maps_file();

    std::cout << "Done reading maps." << std::endl;

    
    for (auto range : _maps._maps_virtual_ranges) {
        for (uint64_t i = range.first; i < range.second; i += PAGE_SIZE) {
            uint64_t page_index = i / PAGE_SIZE;
            uint64_t page_frame;
            
            if (pread(_file_stream, &page_frame, sizeof(page_frame), page_index) != sizeof(page_frame)) {
                exit(-1);
            }

            std::cout << page_frame << std::endl;   
        }
    }
    return;
}

void Pagemap::print_pagemap() {
    _maps.print_maps();
    // std::cout << _pagemap_file << std::endl;
    
    return;
}