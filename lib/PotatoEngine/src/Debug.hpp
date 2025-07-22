#pragma once

#include <string>
#include <filesystem>
#include <fstream>

class Debug_Messages {
private:
    std::filesystem::path debug_log;

    std::ofstream log_file;
public:
    ~Debug_Messages();

    Debug_Messages(std::filesystem::path log);

    std::string Log(std::string message);
};

extern Debug_Messages Debug;
