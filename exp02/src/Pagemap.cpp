#include "Pagemap.h"
#include <fstream>


Pagemap::Pagemap(int pid) : _pid(pid), _maps(pid) {}

void Pagemap::read_pagemap_file() {
    std::cout << "Before reading maps." << std::endl;

    _maps.read_maps_file();
    _maps.parse_maps_file();

    std::cout << "Done reading maps." << std::endl;

    // std::ifstream file_stream(std::string("/proc/") + std::to_string(_pid) + std::string("/pagemap"));
    // _pagemap_file = std::string((std::istreambuf_iterator<char>(file_stream)), std::istreambuf_iterator<char>());

    return;
}

void Pagemap::print_pagemap() {
    _maps.print_maps();
    // std::cout << _pagemap_file << std::endl;
    
    return;
}