#include <cstdio>
#include <cstring>
#include <netinet/in.h>
#include <sstream>
#include <stdexcept>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cerrno>

#include "logger.hpp"
#include "tcpServer.hpp"

using namespace std;


TcpServer::TcpServer(const std::string& addr, const int port)
{
    _servfd = 0;
    _addr = addr;
    _port = port;
}

TcpServer::~TcpServer()
{
    
}


// 调用 Socket 接口，创建客户端套接字
void TcpServer::start() {
    auto logger = Logger::getInstance();

    /*  configure 会对服务器的 IP 地址、端口进行检查，
        此处可认为不需要进行合法性检查。
    */

    // 将地址字符串、端口字符串转换为 network bit
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;       // IPv4
    server_addr.sin_port = htons(_port);    // 网络字节序

    // socket() -> bind() -> listen()

    _servfd = socket(AF_INET, SOCK_STREAM, 0);
    if (_servfd == -1) {
        logger->log(Logger::level::ERROR, "server socket init fail");
        throw std::runtime_error("server socket init fail");
    }   
    
    
    
}


TcpServer::TcpServer() {
    
}


int TcpServer::getSocketFd() {
    return _servfd;
}



void TcpServer::stop() {
    // 其实不能这么修改，需要判断
    if (_servfd != 0) {
        close(_servfd);
    }
}