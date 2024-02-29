#include "Rigidbody.h"

void Rigidbody::AddRelativeForce(Vector3f* force, ForceType forceType)
{
    Vector3f* acceleration = new Vector3f(0.0f, 0.0f, 0.0f);
    Vector3f* F;

    switch (forceType)
    {
    case ForceType::Force:
        _netRelativeForce = Vector3f::Multiply(_netRelativeForce, force);
        break;
    case ForceType::Acceleration:
        // Newton's 2nd Law of motion, F = ma
        acceleration = force;
        F = Vector3f::Scale(acceleration, mass); // 'force' in this case is a property of acceleration.

        // Is this How you Apply an Acceleration?
        _netRelativeForce = Vector3f::Add(_netRelativeForce, F);

        break;
    case ForceType::Impulse:

        break;
    case ForceType::VelocityChange:
        velocity = Vector3f::Add(velocity, force); // 'force' in this case is a change in velocity.


        break;
    }
}

void Rigidbody::AddForce(Vector3f* force, ForceType forceType)
{
    Vector3f* acceleration = new Vector3f(0.0f, 0.0f, 0.0f);
    Vector3f* F;

    switch (forceType)
    {
    case ForceType::Force:
        _netWorldForce = Vector3f::Add(_netWorldForce, force);
        break;
    case ForceType::Acceleration:
        // Newton's 2nd Law of motion, F = ma
        acceleration = force;
        F = Vector3f::Scale(acceleration, mass); // 'force' in this case is a property of acceleration.

        // Is this How you Apply an Acceleration?
        _netWorldForce = Vector3f::Add(_netWorldForce, F);

        break;
    case ForceType::Impulse:
        // A one time force for a short time period (which is why it has to be big)
        break;
    case ForceType::VelocityChange:
        velocity = Vector3f::Add(velocity, force);  // 'force' in this case is a change in velocity.
        break;
    }


}

void Rigidbody::AddRelativeTorque(Vector3f* torque, ForceType forceType)
{
    Vector3f* acceleration = new Vector3f(0.0f, 0.0f, 0.0f);
    Vector3f* F;

    switch (forceType)
    {
    case ForceType::Force:
        _netRelativeTorque = Vector3f::Add(_netRelativeTorque, torque);
        break;
    case ForceType::Acceleration:
        // Newton's 2nd Law of motion, F = ma
        acceleration = torque;
        F = Vector3f::Scale(acceleration, mass); // 'force' in this case is a property of acceleration.

        // Is this How you Apply an Acceleration?
        _netRelativeTorque = Vector3f::Add(_netRelativeTorque,  F);

        break;
    case ForceType::Impulse:
        // A one time force for a short time period (which is why it has to be big)
        break;
    case ForceType::VelocityChange:
        angularVelocity = Vector3f::Add(angularVelocity, torque); // 'force' in this case is a change in velocity.
        break;
    }
}

void Rigidbody::AddTorque(Vector3f* torque, ForceType forceType)
{
    Vector3f* acceleration = new Vector3f(0.0f, 0.0f, 0.0f);
    Vector3f* F;

    switch (forceType)
    {
    case ForceType::Force:
        _netWorldTorque = Vector3f::Add(_netWorldTorque, torque);
        break;
    case ForceType::Acceleration:
        // Newton's 2nd Law of motion, F = ma
        acceleration = torque;
        F = Vector3f::Scale(acceleration, mass); // 'force' in this case is a property of acceleration.

        // Is this How you Apply an Acceleration?
        _netWorldTorque = Vector3f::Add(_netWorldTorque, F);

        break;
    case ForceType::Impulse:
        // A one time force for a short time period (which is why it has to be big)
        break;
    case ForceType::VelocityChange:
        angularVelocity = Vector3f::Add(angularVelocity, torque); // 'force' in this case is a change in velocity.
        break;
    }
}

void Rigidbody::ApplyWorldTranslation()
{
    if (_netWorldForce == Vector3f::ZERO) return;

    // Get the current acceleration
    Acceleration = Vector3f::Divide(_netWorldForce, mass);


    velocity = Vector3f::Add(velocity, Vector3f::Scale(_netWorldForce, VelocityDampening));

    // Apply the new velocity to the current position
    //_transform.position += velocity;
}

void Rigidbody::ApplyLocalTranslation()
{
    if (_netRelativeForce == Vector3f::ZERO) return;

    // Get the current acceleration
    Acceleration = Vector3f::Divide(_netRelativeForce, mass);


    velocity = Vector3f::Add(velocity, Vector3f::Scale(_netRelativeForce, VelocityDampening));

    // Apply a local transformation (maintaining integrity of the Transformation Hierarchy )

    // Apply the new velocity to the current position
    //_transform.localPosition += velocity;
}

void Rigidbody::ApplyLocalRotation()
{
    if (_netRelativeTorque == Vector3f::ZERO) return;

    angularVelocity = Vector3f::Add(angularVelocity, Vector3f::Scale(_netRelativeTorque, AngularDampening));


    // angularVelocity is measured in this case as radians per second.
    Vector3f* eulerAngles = new Vector3f(Rad2Deg * angularVelocity->x, Rad2Deg * angularVelocity->y, Rad2Deg * angularVelocity->z);

    Quaternion* newRotationQ = Quaternion::Euler(eulerAngles->x, eulerAngles->y, eulerAngles->z);


    //_transform.localRotation *= newRotationQ;
}

void Rigidbody::ApplyLocalPhysics()
{
    //ApplyLocalTranslation();
    ApplyLocalRotation();

}

void Rigidbody::ApplyGravity()
{
    Vector3f* up = Vector3f::Up;

    // Gravity is a type of acceleration so must be multiplied by mass.
    Vector3f* forceGravity = Vector3f::Scale(up , -(Gravity * mass));

    //Acceleration = forceGravity;

    AddForce(forceGravity);
}

void Rigidbody::UpdatePhysics()
{
    if (UseGravity)
    {
        ApplyGravity();
    }

    // Forces applied to local position.
    ApplyLocalPhysics();
}