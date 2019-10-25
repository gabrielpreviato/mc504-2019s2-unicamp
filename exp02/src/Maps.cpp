#include "Maps.h"
#include <fstream>


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
        // First we get the line and then we take te virtual page range
        str = _maps_file.substr(0, pos);
        size_t range_pos = str.find(' ');
        str = str.substr(0, range_pos);
    
        _maps_virtual_pages.push_back(str);

        _maps_file.erase(0, pos + delimiter.length());
    }

    return;
}

void Maps::print_maps() {
    for (auto line : _maps_virtual_pages) {
        std::cout << line << std::endl;
    }
    
    return;
}