#include "Point.h"
#include <algorithm>

void Point::update(double dt) {
    Vector3D frictionForce = velocity * (-frictionCoefficient);
    Vector3D totalAcceleration = acceleration + frictionForce;
    
    velocity = velocity + totalAcceleration * dt;
    clampVelocity();
    position = position + velocity * dt;
}

void Point::applyForce(const Vector3D& force) {
    acceleration += force;
    clampAcceleration();
}

void Point::setVelocityLimits(double vmin, double vmax) {
    minVelocity = vmin;
    maxVelocity = vmax;
}

void Point::setAccelerationLimits(double amin, double amax) {
    minAcceleration = amin;
    maxAcceleration = amax;
}

void Point::clampVelocity() {
    double magnitude = velocity.magnitude();
    if (magnitude > maxVelocity) {
        velocity = velocity.normalized() * maxVelocity;
    } else if (magnitude < minVelocity && magnitude > 0.0) {
        velocity = velocity.normalized() * minVelocity;
    }
}

void Point::clampAcceleration() {
    double magnitude = acceleration.magnitude();
    if (magnitude > maxAcceleration) {
        acceleration = acceleration.normalized() * maxAcceleration;
    } else if (magnitude < minAcceleration && magnitude > 0.0) {
        acceleration = acceleration.normalized() * minAcceleration;
    }
}