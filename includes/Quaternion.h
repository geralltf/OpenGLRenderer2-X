#ifndef QUATERNION_H
#define QUATERNION_H

#include<algorithm>

//class Vector2i;
//class Vector3f;
//class Vector2f;
//class Vector4f;
//class Matrix4;
//class Quaternion;

#include "VectorLib.h"
#include "MathLib.h"
#include "Vector2f.h"
#include "Vector3f.h"
#include "Vector4f.h"
#include "Matrix4.h"



class Quaternion
{
public:
    float x;
    float y;
    float z;
    float w;

    Vector2f* xy();
    void xy(float x, float y);

    Vector3f* xyz();
    void xyz(float x, float y, float z);

    Vector4f* xyzw();
    void xyzw(float x, float y, float z, float w);
    void xyzw(Vector4f* value);
    Matrix4* RotationMatrix();

    Matrix4* ToRotationMatrix();

    static Quaternion* Identity();

    Quaternion();

    Quaternion(float x, float y, float z, float w);

    Quaternion(Vector4f* vector);

    Quaternion(Vector3f* vector, float w);

    Quaternion(Matrix4* matrix);

    /// <summary>
    /// Deconstruct quaternion into axis and angle
    /// </summary>
    /// <param name="axis"></param>
    /// <param name="angle"></param>
    void DeconstructQuaternion(Vector3f** axis, float** angle);

    /// <summary>
    /// Deconstruct quaternion into Forward and Up vectors
    /// </summary>
    /// <param name="qOrientation"></param>
    /// <param name="newForwardVector"></param>
    /// <param name="newUpVector"></param>
    void DeconstructQuaternion(Vector3f** newForwardVector, Vector3f** newUpVector);

    /// <summary>
    /// Deconstruct quaternion into Forward and Up vectors
    /// </summary>
    /// <param name="qOrientation"></param>
    /// <param name="newForwardVector"></param>
    /// <param name="newUpVector"></param>
    static void DeconstructQuaternion(Quaternion* qOrientation, Vector3f** newForwardVector, Vector3f** newUpVector);

    static Quaternion* LookRotation(Vector3f* lookAt, Vector3f* up);

    static Quaternion* Euler(float x, float y, float z);

    static Quaternion* FromAxisAngle(Vector3f* axis, float angle);

    void ToAxisAngle(Vector3f** axis, float** angle);

    Vector4f* ToAxisAngle();

    static Quaternion* Slerp(Quaternion* q1, Quaternion* q2, float ratio);

    Quaternion* Conjugate();

    Quaternion* Normalised();

    void Normalise();

    float Magnitude();

    float MagnitudeSquared();

    static Quaternion* FromMatrix(Matrix4* matrix);

    static Quaternion* Add(Quaternion* left, Quaternion* right);

    static Quaternion* Add(Quaternion* left, float right);

    static Quaternion* Subtract(Quaternion* left, Quaternion* right);

    static Quaternion* Subtract(Quaternion* left, float right);

    static Vector4f* Multiply(Quaternion* left, Vector4f* right);

    static Vector3f* Multiply(Quaternion* left, Vector3f* right);

    static Quaternion* Multiply(Quaternion* left, Quaternion* right);

    static Quaternion* Scale(Quaternion* quaternion, float scale);

    static Quaternion* Divide(Quaternion* quaternion, float divider);

    Quaternion* operator+(Quaternion* right) const;

    Quaternion* operator+(float right) const;

    Quaternion* operator-(Quaternion* right) const;

    Quaternion* operator-(float right) const;

    Quaternion* operator*(Quaternion* right) const;

    Vector3f* operator*(Vector3f* right) const;

    Vector2f* operator*(Vector2f* right) const;

    Quaternion* operator*(float right) const;

    Quaternion* operator/(float right) const;
};

#endif