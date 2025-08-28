#include "Force.h"
#include <random>

Vector3D Force::generateForce(std::mt19937& rng) const {
    std::uniform_real_distribution<double> dis(minMagnitude, maxMagnitude);
    
    double magnitude = dis(rng);
    return direction * magnitude;
}