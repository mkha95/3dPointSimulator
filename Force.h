#pragma once
#include "Vector3D.h"
#include <random>

class Force {
public:
    Vector3D direction;
    double minMagnitude;
    double maxMagnitude;
    
    Force() : minMagnitude(0.0), maxMagnitude(0.0) {}
    Force(const Vector3D& dir, double minMag, double maxMag)
        : direction(dir.normalized()), minMagnitude(minMag), maxMagnitude(maxMag) {}
    
    Vector3D generateForce(std::mt19937& rng) const;
};