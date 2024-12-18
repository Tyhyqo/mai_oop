#include "FileLogger.hpp"

FileLogger::FileLogger(const std::string& filename) {
    file_.open(filename, std::ios::app);
}

FileLogger::~FileLogger() {
    if (file_.is_open()) {
        file_.close();
    }
}

void FileLogger::onEvent(const std::string& message) {
    std::lock_guard<std::mutex> lock(file_mtx);
    if (file_.is_open()) {
        file_ << message << std::endl;
    }
}