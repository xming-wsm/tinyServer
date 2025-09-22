#include <cstdio>
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


TcpServer::TcpServer(const std::string& addr, const std::string& port)
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
    // 将地址字符串、端口字符串转换为 network bit
    struct sockaddr_in server_addr;
    server_addr.sin_port = htons(std::stoi(_port));
    server_addr.sin_family = AF_INET;

    // 获取日志模块的 instance
    // auto logger = Logger::getInstance();

    if (inet_pton(AF_INET, _addr.c_str(), &server_addr) != 1 ) {
        // logger->log(Logger::level::ERROR, "Given server IP and Port are invalid");
        throw std::invalid_argument("IP Addr " + _addr + " is invalid");
    } else {
        // std::stringstream ss;
        // ss << "Server IP: " << _addr << "/Port: " << _port;
        // logger->log(Logger::level::INFO, ss.str());
    }
    
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