#include <iostream>
#include <log4cpp/Category.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/Layout.hh>
#include <log4cpp/BasicLayout.hh>

int main(int argc, char* argv[]) {
    // Create a layout instance
    log4cpp::Layout* layout = new log4cpp::BasicLayout();

    // Create appender instances
    log4cpp::FileAppender* fileAppender = new log4cpp::FileAppender("default", "example.log");
    log4cpp::OstreamAppender* consoleAppender = new log4cpp::OstreamAppender("console", &std::cout);

    // Set the layout for each appender
    fileAppender->setLayout(layout);
    consoleAppender->setLayout(layout);

    // Get the root category and set its priority to DEBUG
    log4cpp::Category& root = log4cpp::Category::getRoot();
    root.setPriority(log4cpp::Priority::DEBUG);

    // Add appenders to the root category
    root.addAppender(fileAppender);
    root.addAppender(consoleAppender);

    // Log some messages
    root.error("This is an error message.");
    root.warn("This is a warning message.");
    root.info("This is an informational message.");
    root.debug("This is a debug message.");

    // Clean up
    delete layout;
    delete fileAppender;
    delete consoleAppender;

    return 0;
}
