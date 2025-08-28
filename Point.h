#pragma once
#include "Vector3D.h"

class Point {
public:
    Vector3D position;
    Vector3D velocity;
    Vector3D initialVelocity;
    Vector3D acceleration;
    double frictionCoefficient;
    double minVelocity;
    double maxVelocity;
    double minAcceleration;
    double maxAcceleration;
    
    Point() : frictionCoefficient(0.0), minVelocity(0.0), maxVelocity(0.0), minAcceleration(0.0), maxAcceleration(0.0) {}
    Point(const Vector3D& pos, const Vector3D& vel, const Vector3D& accel, double friction)
        : position(pos), velocity(vel), initialVelocity(vel), acceleration(accel), frictionCoefficient(friction), minVelocity(0.0), maxVelocity(0.0), minAcceleration(0.0), maxAcceleration(0.0) {}
    
    void update(double dt);
    void applyForce(const Vector3D& force);
    void setVelocityLimits(double vmin, double vmax);
    void setAccelerationLimits(double amin, double amax);
    
private:
    void clampVelocity();
    void clampAcceleration();
};