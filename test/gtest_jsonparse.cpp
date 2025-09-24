#include <fstream>
#include <gtest/gtest.h>
#include <istream>
#include <stdio.h>
#include <iostream>

#include "logger.hpp"

// https://github.com/nlohmann/json
#include "json_fwd.hpp"
#include "json.hpp"

using json = nlohmann::json;


TEST(json, parse) {
    std::string ip;
    int port;
    int threadsNums;

    // parse json
    std::ifstream f("/home/threeflowercat/Documents/lookforjob/tinyServer/test/test.json");
    json data;
    if (f.is_open()) {
        data = json::parse(f);
    } else {
        std::cerr << "Can't open files" << std::endl;
    }
    std::string ipaddr = data["server-network-config"]["ip"];
    port = data["server-network-config"]["port"];
    threadsNums = data["server-threads-nums"];

    EXPECT_EQ(ipaddr, "127.0.0.1") << "网络地址解析错误";
    EXPECT_EQ(port, 1245) << "网络端口解析错误";
    EXPECT_EQ(threadsNums, 20) << "线程初始化参数解析错误";
    
}

int main(int argc, const char** argv) {
    Logger::init("/home/threeflowercat/Documents/lookforjob/tinyServer/log/log.txt");
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}