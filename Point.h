#pragma once
#include "Vector3D.h"

class Point {
public:
    Vector3D position;
    Vector3D velocity;
    Vector3D initialVelocity;
    Vector3D acceleration;
    double frictionCoefficient;
    
    Point() : frictionCoefficient(0.0) {}
    Point(const Vector3D& pos, const Vector3D& vel, const Vector3D& accel, double friction)
        : position(pos), velocity(vel), initialVelocity(vel), acceleration(accel), frictionCoefficient(friction) {}
    
    void updatePosition(double time);
    void applyForce(const Vector3D& force);
};