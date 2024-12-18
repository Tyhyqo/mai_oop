#ifndef CONSOLE_LOGGER_HPP
#define CONSOLE_LOGGER_HPP

#include "Observer.hpp"
#include <iostream>
#include <mutex>

class ConsoleLogger : public Observer {
public:
    ConsoleLogger() = default;
    virtual ~ConsoleLogger() = default;
    void onEvent(const std::string& message) override;

private:
    std::mutex cout_mtx;
};

#endif // CONSOLE_LOGGER_HPP