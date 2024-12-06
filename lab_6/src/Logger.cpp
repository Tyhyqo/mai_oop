#include "Logger.hpp"

FileLogger::FileLogger(const std::string& filename) {
    file.open(filename, std::ios::out | std::ios::app);
}

FileLogger::~FileLogger() {
    if (file.is_open()) {
        file.close();
    }
}

void FileLogger::onEvent(const std::string& message) {
    if (file.is_open()) {
        file << message << std::endl;
    }
}

void ConsoleLogger::onEvent(const std::string& message) {
    std::cout << message << std::endl;
}