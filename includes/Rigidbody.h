#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Vector3f.h"
#include "MathExt.h"

enum ForceType
{
    Force = 0,
    Impulse = 1, // Linear Impulse ?
    VelocityChange = 2,
    Acceleration = 5,
};

class Rigidbody
{
public:
    bool UseGravity;
    float mass = 1.0f;
    float Gravity = -9.81f;
    float drag = 0.05f;
    float angularDrag = 0.05f;
    float VelocityDampening = 0.0001f;
    float AngularDampening = 0.0001f;
    Vector3f* LinearMomentum;
    Vector3f* Acceleration;
    Vector3f* velocity;
    Vector3f* angularVelocity;

private:
        Vector3f* _netWorldForce;
        Vector3f* _netWorldTorque;
        Vector3f* _netRelativeForce;
        Vector3f* _netRelativeTorque;
        //Transform _transform;

public:
    void AddRelativeForce(Vector3f* force, ForceType forceType = ForceType::Force);
    void AddForce(Vector3f* force, ForceType forceType = ForceType::Force);
    void AddRelativeTorque(Vector3f* torque, ForceType forceType = ForceType::Force);
    void AddTorque(Vector3f* torque, ForceType forceType = ForceType::Force);

private:
    void ApplyWorldTranslation();
    void ApplyLocalTranslation();
    void ApplyLocalRotation();
    void ApplyLocalPhysics();
    void ApplyGravity();

public: 
    void UpdatePhysics();
};

#endif