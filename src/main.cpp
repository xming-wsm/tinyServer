#include <memory>
#include <iostream>
#include "logger.hpp"
using namespace std;

int main(int argc, char const *argv[])
{
    auto logger = Logger::getInstance("/home/threeflowercat/Documents/lookforjob/tinyServer/log/log.txt");
    logger->log(Logger::level::INFO, "123123123");

    


    return 0;
}
