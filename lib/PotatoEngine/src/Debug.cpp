#include "Debug.hpp"

#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

Debug_Messages::~Debug_Messages() {
    if (log_file.is_open()) {
        log_file.close();
    }
}

Debug_Messages::Debug_Messages(std::filesystem::path log_path) : debug_log(log_path) {
    log_file.open(debug_log);
}

Debug_Messages Debug("debug.log");

std::string Debug_Messages::Log(std::string message) {
    time_t timestamp = time(&timestamp);
    struct tm time_struct = *localtime(&timestamp);
    
    std::string time_string = "[" + std::to_string(time_struct.tm_hour) + ":" + std::to_string(time_struct.tm_min) + ":" + std::to_string(time_struct.tm_sec) + ", ";
    time_string += std::to_string(time_struct.tm_mon) + "-" + std::to_string(time_struct.tm_mday) + "-" + std::to_string(time_struct.tm_year + 1900) + "]: ";

    std::cout << time_string << message << std::endl;

    std::ofstream debug_file;
    log_file << time_string << message << std::endl;

    return message;
}