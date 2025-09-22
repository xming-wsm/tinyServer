#include <memory>
#include <iostream>
#include "logger.hpp"
#include "master_process.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    Logger::init("/home/threeflowercat/Documents/lookforjob/tinyServer/log/log.txt");
    auto logger = Logger::getInstance();
    logger->log(Logger::level::INFO, "Logger init sucess");

    MasterProcess tinyServer;
    tinyServer.run();

    return 0;
}
