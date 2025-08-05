#ifndef LOGGER_H
#define LOGGER_H
#include <iostream>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Category.hh>
using namespace std;
using namespace log4cpp;

#define LOG_WARN(msg) Logger::getInstance()->warn(__FILE__,__LINE__,__FUNCTION__,msg)
#define LOG_ERROR(msg) Logger::getInstance()->error(__FILE__,__LINE__,__FUNCTION__,msg)
#define LOG_DEBUG(msg) Logger::getInstance()->debug(__FILE__,__LINE__,__FUNCTION__,msg)
#define LOG_INFO(msg) Logger::getInstance()->info(__FILE__,__LINE__,__FUNCTION__,msg)

class Logger{
public:
    void warn(const char * file, int line, const char * func, const char * msg);
    void error(const char * file, int line, const char * func, const char * msg);
    void debug(const char * file, int line, const char * func, const char * msg);
    void info(const char * file, int line, const char * func, const char * msg);

    static Logger * getInstance();
    static void destroy();

private:
    Logger();
    ~Logger();
    Logger(const Logger &) = delete;
    Logger & operator=(const Logger &) = delete;
    static Logger * _pInstance;
    static Category * _root;
};

Logger* Logger::_pInstance = nullptr;
Category* Logger::_root = nullptr;

Logger::logger(){
    PatternLayout *layout = new PatternLayout();
    layout->setConversionPattern("%d{%Y-%m-%d %H:%M:%S} %-5p [%F:%L] %m%n");

    OstreamAppender *consoleAppender = new OstreamAppender("console", &cout);
    consoleAppender->setLayout(layout);

    FileAppender *fileAppender = new FileAppender("file", "app.log");
    fileAppender->setLayout(layout);

    _root = &Category::getRoot();
    _root->addAppender(consoleAppender);
    _root->addAppender(fileAppender);
}
Logger::～Logger() {
    Category::shutdown();
}
void Logger::destroy() {
    if (_pInstance != nullptr) {
        delete _pInstance;
        _pInstance = nullptr;
    }
}
Logger * Logger::getInstance(){
    if(_pInstance == null){
        _pInstance = new Logger();
    }
    return _pInstance;
}
void Logger::warn(const char *file, int line, const char *func, const char *msg) {
    _root->warnStream() << "[" << file << ":" << line << "] " << func << "() - " << msg;
}

void Logger::error(const char *file, int line, const char *func, const char *msg) {
    _root->errorStream() << "[" << file << ":" << line << "] " << func << "() - " << msg;
}

void Logger::debug(const char *file, int line, const char *func, const char *msg) {
    _root->debugStream() << "[" << file << ":" << line << "] " << func << "() - " << msg;
}

void Logger::info(const char *file, int line, const char *func, const char *msg) {
    _root->infoStream() << "[" << file << ":" << line << "] " << func << "() - " << msg;
}

void warn(const char * file, int line, const char * func, const char * msg){
    _root->warnStream() << "[" << file << ":" << line << "] " << func << "() - " << msg;
}

#endif
