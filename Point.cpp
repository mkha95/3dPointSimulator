#include "Point.h"

void Point::updatePosition(double time) {
    Vector3D frictionForce = velocity * (-frictionCoefficient);
    Vector3D totalAcceleration = acceleration + frictionForce;
    
    position = position + initialVelocity * time + totalAcceleration * (0.5 * time * time);
    velocity = initialVelocity + totalAcceleration * time;
}

void Point::applyForce(const Vector3D& force) {
    acceleration += force;
}