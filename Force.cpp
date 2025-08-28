#include "Force.h"
#include <random>

Vector3D Force::generateForce() const {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(minMagnitude, maxMagnitude);
    
    double magnitude = dis(gen);
    return direction * magnitude;
}