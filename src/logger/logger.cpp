#include <chrono>
#include <cstdlib>
#include <ctime>
#include <ios>
#include <iostream>
#include <ostream>
#include <cerrno>
#include <cstring>
#include <sched.h>
#include <sstream>
#include <string>
#include <thread>

#include <sys/types.h>
#include <unistd.h>

#include "logger.hpp"

using namespace std;




// 单例模式接口
shared_ptr<Logger> Logger::getInstance(const string& log_path) {
    static shared_ptr<Logger> instance(new Logger(log_path));
    return instance;
}


void Logger::log(level l, const string& msg) {
    _log_mtx.lock();

    // 获取当前时间
    chrono::system_clock::time_point curTime = chrono::system_clock::now();
    time_t time = chrono::system_clock::to_time_t(curTime);
    string time_str = std::asctime(std::localtime(&time));
    time_str.pop_back(); // 去掉 std::asctime() 自带的换行符

    // 获取进程ID/线程ID
    pid_t processID = getpid();
    // std::thread::id threadID = std::this_thread::get_id();
    // std::stringstream idStream;
    // idStream << threadID;


    string level_str;
    switch (l) {
        case level::INFO:  level_str = "[info]"; break;
        case level::WARN:  level_str = "[warn]"; break;
        case level::ERROR:  level_str = "[error]"; break;
        default:    level_str = "[unknown]"; break;
    }

    string fmtmsg = 
        level_str + " " + 
        time_str + " " +  
        "pid:" + to_string(processID) + ": " + 
        msg + "\n";


    // 写入文件中
    if (_log_file.good()) {
        _log_file << fmtmsg;
        _log_file.flush();
    } else {
        cerr << "写入日志文件失败" << endl;
    }

    _log_mtx.unlock();
}



Logger::Logger(const string& log_path) : _log_path(log_path) {
    try {
        _log_file.exceptions(ios::failbit | ios::badbit);    // 设置异常掩码
        _log_file.open(log_path, ios::app | ios::out);
    } 
    catch (const ios_base::failure& e) {
        cerr << "Can't open file: " << e.what() << ": ";
        cout << strerror(errno) << endl;
    }
    
}

