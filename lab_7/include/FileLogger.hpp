#ifndef FILE_LOGGER_HPP
#define FILE_LOGGER_HPP

#include "Observer.hpp"
#include <string>
#include <fstream>
#include <mutex>

class FileLogger : public Observer {
public:
    FileLogger(const std::string& filename);
    virtual ~FileLogger();
    void onEvent(const std::string& message) override;

private:
    std::ofstream file_;
    std::mutex file_mtx;
};

#endif // FILE_LOGGER_HPP