#include "master_process.hpp"
#include "logger.hpp"
#include "tcpServer.hpp"
#include "configure.hpp"
#include <memory>
#include <stdexcept>
#include <string>


/*
    run() 是主线程的核心函数，在 run（）
 */
void MasterProcess::run() {
    // 获取日志单例
    auto logger = Logger::getInstance();
    
    unique_ptr<TcpServer> server = nullptr;


    // 读取配置文件，并启动服务器
    try {
        Configure config("/home/threeflowercat/Documents/lookforjob/tinyServer/server-config.json");
        server = make_unique<TcpServer>(config.getIpAddr(), config.getIpPort());
        server->start();
    } 
    catch (const std::invalid_argument& e) {
        
    }

    // 获取服务端 Socket 文件描述符
    int servfd = server->getSocketFd();
    logger->log(Logger::level::INFO, "Server socket description: " + std::to_string(servfd));



}




MasterProcess::MasterProcess() {

}


MasterProcess::~MasterProcess() {

}


