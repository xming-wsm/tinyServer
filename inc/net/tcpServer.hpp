#ifndef TCPSERVER_HPP
#define TCPSERVER_HPP

#include <string>



class TcpServer
{
public:
    TcpServer(const std::string& addr, const int port);
    TcpServer();
    ~TcpServer();

    
    int getSocketFd();
    void start();
    void stop();
private:
    // servfd 要传递给主进程中的 epoll 函数，设置为 private 合理吗？
    int _servfd;            // 服务端 Socket 文件描述符;
    
    std::string _addr;      // 服务器 IP 地址
    int _port;              // 服务器端口号

};






#endif // TCPSERVER_HPP