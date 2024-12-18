#include "ConsoleLogger.hpp"

void ConsoleLogger::onEvent(const std::string& message) {
    std::lock_guard<std::mutex> lock(cout_mtx);
    std::cout << message << std::endl;
}