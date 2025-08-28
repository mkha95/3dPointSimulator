#include "Simulator.h"
#include "VTKWriter.h"
#include <iostream>
#include <iomanip>

Simulator::Simulator(const SimulationParams& params) : params(params), rng(std::random_device{}()) {
    initializeForces();
    initializePoints();
}

void Simulator::initializePoints() {
    points.clear();
    points.reserve(params.numPoints);
    
    for (int i = 0; i < params.numPoints; ++i) {
        Vector3D position = randomVector3D(-params.cubeSize / 2.0, params.cubeSize / 2.0);
        Vector3D velocity = randomVector3D(params.minVelocity, params.maxVelocity);
        Vector3D initialVelocity = randomVector3D(params.minInitialVelocity, params.maxInitialVelocity);
        Vector3D acceleration = randomVector3D(params.minAcceleration, params.maxAcceleration);
        double friction = randomDouble(params.minFriction, params.maxFriction);
        
        Point point(position, velocity, acceleration, friction);
        point.initialVelocity = initialVelocity;
        
        for (const auto& force : forces) {
            Vector3D forceVector = force.generateForce();
            point.applyForce(forceVector);
        }
        
        points.push_back(point);
    }
}

void Simulator::initializeForces() {
    forces.clear();
    forces.reserve(params.numForces);
    
    for (int i = 0; i < params.numForces; ++i) {
        Vector3D direction = randomVector3D(-1.0, 1.0).normalized();
        double minMag = randomDouble(params.minAcceleration, params.maxAcceleration);
        double maxMag = minMag + randomDouble(0.0, params.maxAcceleration - minMag);
        
        forces.emplace_back(direction, minMag, maxMag);
    }
}

void Simulator::simulate() {
    std::cout << std::fixed << std::setprecision(3);
    
    if (params.enableVTKOutput) {
        pointsHistory.clear();
        pointsHistory.reserve(params.simulationTime + 1);
    }
    
    for (int t = 0; t <= params.simulationTime; ++t) {
        std::cout << "Time: " << t << " seconds\n";
        std::cout << "====================\n";
        
        for (size_t i = 0; i < points.size(); ++i) {
            points[i].updatePosition(static_cast<double>(t));
        }
        
        if (params.enableVTKOutput) {
            pointsHistory.push_back(points);
        }
        
        printPointPositions(t);
        
        if (params.enableVTKOutput && !params.vtkOutputFile.empty()) {
            VTKWriter::writePoints(points, params.vtkOutputFile, t);
        }
        
        std::cout << "\n";
    }
    
    if (params.enableVTKOutput && !params.vtkOutputFile.empty()) {
        VTKWriter::writeTimeSeriesPoints(pointsHistory, params.vtkOutputFile);
    }
}

void Simulator::printPointPositions(int) const {
    for (size_t i = 0; i < points.size(); ++i) {
        const auto& pos = points[i].position;
        std::cout << "Point " << i << ": (" 
                  << pos.x << ", " << pos.y << ", " << pos.z << ")\n";
    }
}

double Simulator::randomDouble(double min, double max) {
    std::uniform_real_distribution<double> dis(min, max);
    return dis(rng);
}

Vector3D Simulator::randomVector3D(double min, double max) {
    return Vector3D(
        randomDouble(min, max),
        randomDouble(min, max),
        randomDouble(min, max)
    );
}