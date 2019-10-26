#include "Pagemap.h"
#include <fstream>
#include <sstream>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>

#define PAGE_SIZE 0x1000


Pagemap::Pagemap(int pid) : _pid(pid), _maps(pid), 
                            _file_stream(open((std::string("/proc/") + std::to_string(_pid) + std::string("/pagemap")).c_str(), O_RDONLY)) {
    
    std::cout << _file_stream << std::endl;
}

void Pagemap::read_pagemap_file() {
    std::cout << "Before reading maps." << std::endl;

    _maps.read_maps_file();
    _maps.parse_maps_file();

    std::cout << "Done reading maps." << std::endl;

    std::cout << "PAGE SIZE: " << PAGE_SIZE << std::endl;
    
    for (auto range : _maps._maps_virtual_ranges) {
        for (uint64_t i = range.first; i < range.second; i += PAGE_SIZE) {
            std::cout << "i: " << i << ", range: " << range.first << '-' << range.second << std::endl;
            
            uint64_t page_frame;
            uint64_t page_index = i / PAGE_SIZE * sizeof(page_frame);

            std::cout << "page index: " << page_index << std::endl;
            
            int ret = pread(_file_stream, &page_frame, sizeof(page_frame), page_index);
            if (ret == -1) {
                exit(-1);
            }
            else if (ret == 0) {
                std::cout << "EOF" << std::endl;    
            }
            else if (ret = sizeof(page_frame)) {
                std::stringstream sstream;
                sstream << std::hex << page_frame;
                std::string result = sstream.str();

                std::cout << "Page frame: 0x" << result << std::endl;
            }
            else {
                exit(-2);
            }
        }
    }

    return;
}

void Pagemap::print_pagemap() {
    // _maps.print_maps();
    // std::cout << _pagemap_file << std::endl;
    
    return;
}