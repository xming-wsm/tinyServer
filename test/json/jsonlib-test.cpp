#include <fstream>
#include <istream>
#include <stdio.h>
#include <iostream>

// https://github.com/nlohmann/json

#include "../../lib/json/json_fwd.hpp"
#include "../../lib/json/json.hpp"

using json = nlohmann::json;


int main(int argc, const char** argv) {
    std::string ip;
    int port;
    int threadsNums;

    // parse json
    std::ifstream f("../test.json");
    json data;
    if (f.is_open()) {
        data = json::parse(f);
    } else {
        std::cerr << "Can't open files" << std::endl;
    }
    std::string ipaddr = data["server-network-config"]["ip"];
    std::cout << std::setw(4) << data << std::endl;
    std::cout << ipaddr << std::endl;
    std::cout << data["server-network-config"]["port"] << std::endl;
    return 0;
}