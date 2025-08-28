#include "ConfigParser.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

bool ConfigParser::parseConfigFile(const std::string& filename, SimulationParams& params) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open config file: " << filename << std::endl;
        return false;
    }
    
    params.enableVTKOutput = false;
    params.vtkOutputFile = "";
    
    std::string line;
    int lineNumber = 0;
    
    while (std::getline(file, line)) {
        lineNumber++;
        trim(line);
        
        if (line.empty() || line[0] == '#') {
            continue;
        }
        
        auto [key, value] = parseLine(line);
        if (key.empty()) {
            std::cerr << "Warning: Invalid line " << lineNumber << " in config file: " << line << std::endl;
            continue;
        }
        
        try {
            if (key == "cube_size" || key == "L") {
                params.cubeSize = std::stod(value);
            } else if (key == "num_points" || key == "N") {
                params.numPoints = std::stoi(value);
            } else if (key == "min_friction" || key == "a1") {
                params.minFriction = std::stod(value);
            } else if (key == "max_friction" || key == "a2") {
                params.maxFriction = std::stod(value);
            } else if (key == "num_forces" || key == "M") {
                params.numForces = std::stoi(value);
            } else if (key == "min_acceleration" || key == "amin") {
                params.minAcceleration = std::stod(value);
            } else if (key == "max_acceleration" || key == "amax") {
                params.maxAcceleration = std::stod(value);
            } else if (key == "min_velocity" || key == "vmin") {
                params.minVelocity = std::stod(value);
            } else if (key == "max_velocity" || key == "vmax") {
                params.maxVelocity = std::stod(value);
            } else if (key == "min_initial_velocity" || key == "v0min") {
                params.minInitialVelocity = std::stod(value);
            } else if (key == "max_initial_velocity" || key == "v0max") {
                params.maxInitialVelocity = std::stod(value);
            } else if (key == "simulation_time" || key == "T") {
                params.simulationTime = std::stoi(value);
            } else if (key == "vtk_output_file") {
                params.vtkOutputFile = value;
                params.enableVTKOutput = !value.empty();
            } else {
                std::cerr << "Warning: Unknown parameter '" << key << "' on line " << lineNumber << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: Invalid value '" << value << "' for parameter '" << key 
                      << "' on line " << lineNumber << std::endl;
            return false;
        }
    }
    
    return true;
}

bool ConfigParser::isConfigFile(const std::string& filename) {
    size_t dotPos = filename.find_last_of('.');
    if (dotPos == std::string::npos) {
        return false;
    }
    
    std::string extension = filename.substr(dotPos + 1);
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
    
    return (extension == "cfg" || extension == "config" || extension == "conf");
}

void ConfigParser::trim(std::string& str) {
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), str.end());
}

std::pair<std::string, std::string> ConfigParser::parseLine(const std::string& line) {
    size_t equalPos = line.find('=');
    if (equalPos == std::string::npos) {
        return {"", ""};
    }
    
    std::string key = line.substr(0, equalPos);
    std::string value = line.substr(equalPos + 1);
    
    trim(key);
    trim(value);
    
    std::transform(key.begin(), key.end(), key.begin(), ::tolower);
    
    return {key, value};
}