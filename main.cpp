#include "Simulator.h"
#include "ConfigParser.h"
#include <iostream>
#include <string>
#include <cstdlib>

void printUsage() {
    std::cout << "Usage: 3DPointSimulator <config_file>\n";
    std::cout << "   OR: 3DPointSimulator <L> <N> <a1> <a2> <M> <amin> <amax> <vmin> <vmax> <v0min> <v0max> <T> [vtk_output_file]\n\n";
    std::cout << "Config file mode:\n";
    std::cout << "  config_file     - Configuration file (.cfg, .config, or .conf extension)\n\n";
    std::cout << "Command line mode parameters:\n";
    std::cout << "  L               - Cube side length\n";
    std::cout << "  N               - Number of points\n";
    std::cout << "  a1              - Minimum friction coefficient\n";
    std::cout << "  a2              - Maximum friction coefficient\n";
    std::cout << "  M               - Number of forces\n";
    std::cout << "  amin            - Minimum acceleration\n";
    std::cout << "  amax            - Maximum acceleration\n";
    std::cout << "  vmin            - Minimum velocity\n";
    std::cout << "  vmax            - Maximum velocity\n";
    std::cout << "  v0min           - Minimum initial velocity\n";
    std::cout << "  v0max           - Maximum initial velocity\n";
    std::cout << "  T               - Simulation duration (seconds)\n";
    std::cout << "  vtk_output_file - Optional VTK output filename (without extension)\n";
}

int main(int argc, char* argv[]) {
    if (argc != 2 && argc != 13 && argc != 14) {
        std::cerr << "Error: Incorrect number of arguments.\n\n";
        printUsage();
        return 1;
    }
    
    try {
        SimulationParams params;
        
        // Check if using config file mode
        if (argc == 2) {
            std::string arg = argv[1];
            if (ConfigParser::isConfigFile(arg)) {
                if (!ConfigParser::parseConfigFile(arg, params)) {
                    std::cerr << "Error: Failed to parse config file: " << arg << std::endl;
                    return 1;
                }
            } else {
                std::cerr << "Error: Single argument must be a config file (.cfg, .config, or .conf)\n\n";
                printUsage();
                return 1;
            }
        } else {
            // Command line parameter mode
            params.cubeSize = std::stod(argv[1]);
            params.numPoints = std::stoi(argv[2]);
            params.minFriction = std::stod(argv[3]);
            params.maxFriction = std::stod(argv[4]);
            params.numForces = std::stoi(argv[5]);
            params.minAcceleration = std::stod(argv[6]);
            params.maxAcceleration = std::stod(argv[7]);
            params.minVelocity = std::stod(argv[8]);
            params.maxVelocity = std::stod(argv[9]);
            params.minInitialVelocity = std::stod(argv[10]);
            params.maxInitialVelocity = std::stod(argv[11]);
            params.simulationTime = std::stoi(argv[12]);
            
            params.enableVTKOutput = (argc == 14);
            params.vtkOutputFile = params.enableVTKOutput ? std::string(argv[13]) : "";
        }
        
        if (params.cubeSize <= 0 || params.numPoints <= 0 || params.numForces <= 0 || params.simulationTime < 0) {
            std::cerr << "Error: Invalid parameter values. All values must be positive (except T which can be 0).\n";
            return 1;
        }
        
        if (params.minFriction > params.maxFriction || 
            params.minAcceleration > params.maxAcceleration ||
            params.minVelocity > params.maxVelocity ||
            params.minInitialVelocity > params.maxInitialVelocity) {
            std::cerr << "Error: Minimum values cannot be greater than maximum values.\n";
            return 1;
        }
        
        std::cout << "3D Physics Point Simulation\n";
        std::cout << "============================\n";
        std::cout << "Cube size: " << params.cubeSize << "\n";
        std::cout << "Number of points: " << params.numPoints << "\n";
        std::cout << "Friction range: [" << params.minFriction << ", " << params.maxFriction << "]\n";
        std::cout << "Number of forces: " << params.numForces << "\n";
        std::cout << "Acceleration range: [" << params.minAcceleration << ", " << params.maxAcceleration << "]\n";
        std::cout << "Velocity range: [" << params.minVelocity << ", " << params.maxVelocity << "]\n";
        std::cout << "Initial velocity range: [" << params.minInitialVelocity << ", " << params.maxInitialVelocity << "]\n";
        std::cout << "Simulation time: " << params.simulationTime << " seconds\n";
        if (params.enableVTKOutput) {
            std::cout << "VTK output file: " << params.vtkOutputFile << "\n";
        }
        std::cout << "\n";
        
        Simulator simulator(params);
        simulator.simulate();
        
    } catch (const std::exception& e) {
        std::cerr << "Error parsing arguments: " << e.what() << "\n\n";
        printUsage();
        return 1;
    }
    
    return 0;
}