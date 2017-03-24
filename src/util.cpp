#include <iostream>
#include <vector>
#include <sstream>

#include "util.h"


std::vector<std::string> Util::splitString(const std::string stringToSplit) {
    std::vector<std::string> vec_return;
    std::stringstream ss(stringToSplit);
    std::string chunk;

    while(std::getline(ss, chunk, ',')) {
        vec_return.push_back(chunk);
    }

    return vec_return;
}
