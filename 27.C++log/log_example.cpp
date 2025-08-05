#include <log4cpp/Category.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/Priority.hh>

int main(int argc, char** argv) {
    // 创建一个输出到标准输出的 appender
    log4cpp::OstreamAppender* osAppender = new log4cpp::OstreamAppender("osAppender", &std::cout);
    osAppender->setLayout(new log4cpp::BasicLayout());

    // 获取 root category 并添加 appender
    log4cpp::Category& root = log4cpp::Category::getRoot();
    root.addAppender(osAppender);

    // 记录不同级别的日志
    root.info("This is an info message");
    root.warn("This is a warning");
    root.error("This is an error");

    // 关闭 log4cpp
    log4cpp::Category::shutdown();
    return 0;
}
