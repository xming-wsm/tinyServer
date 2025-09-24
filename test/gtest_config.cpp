#include <gtest/gtest.h>
#include "configure.hpp"
#include "logger.hpp"




TEST(configure, configFileExit) {
    Configure config("/home/threeflowercat/Documents/lookforjob/tinyServer/server-config.json");   
}

TEST(configure, configFileNotExit) {
    Configure config("/home/threeflowercat/Documents/lookforjob/tinyServer/test/test.json");
}