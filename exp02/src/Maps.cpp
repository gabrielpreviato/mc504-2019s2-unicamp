#include "Maps.h"
#include <fstream>


void Maps::read_map_file() {
    std::ifstream file_stream(std::string("/proc/") + std::to_string(_pid) + std::string("/maps"));
    _maps_file = std::string((std::istreambuf_iterator<char>(file_stream)), std::istreambuf_iterator<char>());
    
    return;
}