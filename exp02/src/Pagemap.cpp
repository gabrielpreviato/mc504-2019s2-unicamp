#include "Pagemap.h"
#include <fstream>


void Pagemap::read_pagemap_file() {
    std::cout << "Before reading." << std::endl;

    std::ifstream file_stream(std::string("/proc/") + std::to_string(_pid) + std::string("/pagemap"));
    _pagemap_file = std::string((std::istreambuf_iterator<char>(file_stream)), std::istreambuf_iterator<char>());
    
    std::cout << "Done reading." << std::endl;

    return;
}

void Pagemap::print_pagemap() {
    std::cout << _pagemap_file << std::endl;
    
    return;
}