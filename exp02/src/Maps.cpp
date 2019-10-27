// Copyright 2019 Gabriel Previato @ UNICAMP.
//
// All components of this repository are licensed under the MIT License.
// See LICENSE.txt for details.

#include "Maps.h"
#include <fstream>

#define PAGE_SIZE 0x1000


void Maps::read_maps_file() {
    std::ifstream file_stream(std::string("/proc/") + std::to_string(_pid) + std::string("/maps"));
    _maps_file = std::string((std::istreambuf_iterator<char>(file_stream)), std::istreambuf_iterator<char>());

    return;
}

void Maps::parse_maps_file() {
    size_t pos = 0;
    std::string delimiter = "\n";
    std::string str;

    while ((pos = _maps_file.find(delimiter)) != std::string::npos) {
        // First we get the line and then we take te virtual page range string
        str = _maps_file.substr(0, pos);
        size_t range_pos = str.find(' ');
        str = str.substr(0, range_pos);

        // Takes maps ranges string and parses it to u_int64
        std::string first, last;
        size_t minus_pos = str.find('-');
        first = str.substr(0, minus_pos);
        last = str.substr(minus_pos + 1);

        _maps_virtual_ranges.push_back({std::stoull(first, 0, 16), std::stoull(last, 0, 16)});

        _maps_virtual_pages.push_back(str);

        _maps_file.erase(0, pos + delimiter.length());
    }

    return;
}

void Maps::print_maps() {
    for (auto pair : _maps_virtual_ranges) {
        std::cout << pair.first << '-' << pair.second << std::endl;
    }

    return;
}
