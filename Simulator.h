#pragma once
#include "Point.h"
#include "Force.h"
#include <vector>
#include <random>

struct SimulationParams {
    double cubeSize;
    int numPoints;
    double minFriction;
    double maxFriction;
    int numForces;
    double minAcceleration;
    double maxAcceleration;
    double minVelocity;
    double maxVelocity;
    double minInitialVelocity;
    double maxInitialVelocity;
    int simulationTime;
    std::string vtkOutputFile;
    bool enableVTKOutput;
};

class Simulator {
private:
    std::vector<Point> points;
    std::vector<Force> forces;
    std::vector<std::vector<Point>> pointsHistory;
    SimulationParams params;
    std::mt19937 rng;
    
public:
    Simulator(const SimulationParams& params);
    
    void initializePoints();
    void initializeForces();
    void simulate();
    void printPointPositions(int timeStep) const;
    
private:
    double randomDouble(double min, double max);
    Vector3D randomVector3D(double min, double max);
};