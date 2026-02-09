#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <memory>
#include <chrono>
#include <string>
#include <sstream>
#include <map>
#include <iomanip>
#include <utility>

class Log
{
public:
    template <typename... Args>
    static void Msg(std::string tag, Args &&...args)
    {
        std::cout << tag << " | ";
        (std::cout << ... << args) << " | " << CurrentTime() << '\n';
    }

    static std::string CurrentTime()
    {
        using namespace std::chrono;

        auto now = system_clock::now();
        auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

        std::time_t t = system_clock::to_time_t(now);
        std::tm tm = *std::localtime(&t);

        std::ostringstream oss;
        oss << std::setfill('0')
            << std::setw(2) << tm.tm_hour << ":"
            << std::setw(2) << tm.tm_min << ":"
            << std::setw(2) << tm.tm_sec << ":"
            << std::setw(3) << ms.count();

        return oss.str();
    }
};
#endif