#ifndef LOGGER_HH
#define LOGGER_HH


#include <fstream>
#include <string>
#include <mutex>
#include <memory>

using namespace std;

/**
 *  基于 C++ 的简单日志库系统
 *  Logger 采用单例模式设计（饿汉式），在启动时就创建
 *  
 *  存储方式：文本文件
 *  存储内容：时间 + 日志级别 + 进程ID/线程ID + 文本信息
 *  日志级别：INFO, WARN, ERROR
 */
class Logger {
public:
    enum class level { 
        INFO,
        WARN,
        ERROR
    };

    // 单例模式接口
    static shared_ptr<Logger> getInstance(const string& log_path);

    void log(level l, const string& msg);
private:
    Logger(const string& log_path);             // 私有化构造函数
    Logger(const Logger&) = delete;             // 禁止拷贝
    Logger& operator=(const Logger&) = delete;  // 禁止运算符重载

    ofstream _log_file;     // 日志文件对象
    string   _log_path;     // 日志文件路径
    mutex    _log_mtx;      // 日志互斥锁
};






























#endif /* LOGGER_H */