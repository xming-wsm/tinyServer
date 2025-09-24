#ifndef CONFIGURE_HPP
#define CONFIGURE_HPP


#include <fstream>
#include <string>

using namespace std;



class Configure {
public:
    explicit Configure(const string& configPath);
    Configure();
    ~Configure();
    
    string getIpAddr() const;
    int getIpPort() const;
    int getThreadInitNums() const;
    int getMaxClients() const;
private:
    ifstream configFile;    // 配置文件流

    // 将需要解析的参数定义为私有变量，合适吗？
    string _ipaddr;      // 服务器 IP 地址
    int _port;           // 服务器端口号
    int _maxClients;     // 最多客户端数量
    int _threadNums;     // 线程池线程数量

};








#endif // !CONFIGURE_HPP