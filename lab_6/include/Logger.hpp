#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "Observer.hpp"
#include <fstream>
#include <iostream>

class FileLogger : public Observer {
public:
    FileLogger(const std::string& filename);
    ~FileLogger();
    void onEvent(const std::string& message) override;

private:
    std::ofstream file;
};

class ConsoleLogger : public Observer {
public:
    void onEvent(const std::string& message) override;
};

#endif // LOGGER_HPP