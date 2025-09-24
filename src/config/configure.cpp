#include <arpa/inet.h>
#include <cerrno>
#include <cstring>
#include <ios>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <sys/socket.h>


#include "configure.hpp"
#include "logger.hpp"

#include "json.hpp"
#include "json_fwd.hpp"
using JSON = nlohmann::json;

using namespace std;

// 辅助函数，用于更新日志和抛出异常行为
void logAndThrow(shared_ptr<Logger> logger, Logger::level l, const string& msg) {
    logger->log(l, msg);
    throw std::invalid_argument(msg);
    cout << "testing" << endl;
}



Configure::Configure(const string& configPath) {
    auto logger = Logger::getInstance();
    try {   
        // 设置异常码
        configFile.exceptions(std::ios::badbit | std::ios::failbit);
        configFile.open(configPath, std::ios::in);
    }
    catch (const ios_base::failure& e) {
        string msg = "Can't open server-config.json: " + string(strerror(errno));
        // 抛出异常，终止构造函数
        logAndThrow(logger, Logger::level::ERROR, msg);
    }

    try {
        JSON jsonPraser = JSON::parse(configFile);
        // 检查 json 是否包含 server 域
        if (!jsonPraser.contains("server")) {
            logAndThrow(logger, Logger::level::ERROR, "Json missing 'server' filed");    
        }

        // 使用引用，避免多余的拷贝操作
        auto& jsonServer = jsonPraser["server"];
        if (!jsonServer.contains("ip")) 
            logAndThrow(logger, Logger::level::ERROR, "Json Mssing 'ip' fild");
        if (!jsonServer.contains("port")) 
            logAndThrow(logger, Logger::level::ERROR, "Json Mssing 'port' fild");
        if (!jsonServer.contains("max-client")) 
            logAndThrow(logger, Logger::level::ERROR, "Json Mssing 'max-client' fild");
        
        // 解析服务器 IP 配置，并进行错误检查
        _ipaddr = jsonServer["ip"];
        if (inet_addr(_ipaddr.c_str()) == -1) {
            logAndThrow(logger, Logger::level::ERROR, "Invalid ip address in config");
        }

        // 解析端口号
        _port = jsonServer["port"];
        if (_port < 0 || _port > 65535) {
            logAndThrow(logger, Logger::level::ERROR, "Invalid port in config, must in (0~65535)");
        }

        // 解析最大客户端数量连接数
        _maxClients = jsonServer["max-client"];
        if (_maxClients <= 0 || _maxClients > 1000) {
            logAndThrow(logger, Logger::level::ERROR, "Invalid max-client in config, must in (0~1000)");
        }

    }
    catch (const JSON::exception& e) {
        string msg = "json parse error" + string(e.what());
        logAndThrow(logger, Logger::level::ERROR, msg);
    }
    
    logger->log(Logger::level::INFO, "config init success");
}


Configure::Configure() {
    
}

Configure::~Configure() {
    
}


string Configure::getIpAddr() const {
    return _ipaddr;
}

int Configure::getIpPort() const {
    return _port;
}

int Configure::getThreadInitNums() const {
    return _threadNums;
}

int Configure::getMaxClients() const {
    return _maxClients;
}