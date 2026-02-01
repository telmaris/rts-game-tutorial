#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <memory>
#include <chrono>
#include <string>
#include <sstream>
#include <map>
class Log
{
    public:
    template<typename... Args>
    static void Msg(std::string tag, Args&&... args)
    {
        std::cout << tag << " | ";
        (std::cout << ... << args) << '\n';
    }
};
/*int TimeLapsed(int length)
{
    auto autisticLength = std::chrono::seconds(length);
    auto start = std::chrono::high_resolution_clock::to_time_t(autisticLength);

}*/
#endif