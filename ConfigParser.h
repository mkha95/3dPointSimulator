#pragma once
#include "Simulator.h"
#include <string>

class ConfigParser {
public:
    static bool parseConfigFile(const std::string& filename, SimulationParams& params);
    static bool isConfigFile(const std::string& filename);
    
private:
    static void trim(std::string& str);
    static std::pair<std::string, std::string> parseLine(const std::string& line);
};