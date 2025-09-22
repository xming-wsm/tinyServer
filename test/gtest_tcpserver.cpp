#include <gtest/gtest.h>
#include "tcpServer.hpp"


TEST(TcpServer, init) {
    TcpServer server("127.0.0.0", "9009");
    server.start();
    EXPECT_NE(0, server.getSocketFd()) 
        << "server socket fd is zero!!!";
}





int main(int argc, char const *argv[])
{
    /* code */
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
