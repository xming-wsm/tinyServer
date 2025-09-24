#include <gtest/gtest.h>
#include "tcpServer.hpp"


TEST(TcpServer, init) {
    TcpServer server("127.0.0.0", 9009);
    server.start();
    EXPECT_NE(0, server.getSocketFd()) 
        << "server socket fd is zero!!!";
}



