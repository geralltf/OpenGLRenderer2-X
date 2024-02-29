#ifndef VECTOR3F_H
#define VECTOR3F_H

//class Vector2i;
//class Vector3f;
//class Vector2f;
//class Vector4f;
//class Matrix4;
//class Quaternion;

#include "VectorLib.h"
#include "Vector2f.h"
#include "Vector4f.h"
#include "Matrix4.h"

class Vector3f
{
public:
    static Vector3f* ZERO;
    static Vector3f* ONE;
    static Vector3f* Forward;
    static Vector3f* Back;
    static Vector3f* Left;
    static Vector3f* Right;
    static Vector3f* Up;
    static Vector3f* Down;
    static Vector3f* UnitX;
    static Vector3f* UnitY;
    static Vector3f* UnitZ;

    float x;
    float y;
    float z;

    Vector3f();
    Vector3f(int x, int y, int z);

    Vector3f(float x, float y, float z);

    Vector3f* Normalised();
    //float MagnitudeSquared();

    //float Magnitude();

    Vector2f* xy();
    void xy(Vector2f* value);
    Vector3f* xyz();
    void xy(Vector3f* value);
    Vector4f* xyzw();
    void xyzw(Vector4f* value);

    float* ToArray();

    Vector3f* TransformVector(Matrix4* transformationMatrix);

    Vector3f* Add(Vector3f* v);

    Vector3f* Multiply(Vector3f* value);

    Vector3f* Scale(float scalar);

    Vector3f* Normalise();

    float MagnitudeSquared();

    float Magnitude();

    static float Distance(Vector3f* source, Vector3f* target);

    static float DistanceSquared(Vector3f* source, Vector3f* target);

    static float Dot(Vector3f* left, Vector3f* right);

    static Vector3f* Cross(Vector3f* left, Vector3f* right);

    static float Crossf(Vector3f* left, Vector3f* right);

    static Vector3f* Lerp(Vector3f* from, Vector3f* to, float ratio);

    static Vector3f* TriangleLerp(Vector3f* a, Vector3f* b, Vector3f* c, float u, float v);

    static Vector3f* BarycetricInterpolator(Vector3f* a, Vector3f* b, Vector3f* c, float ratioX, float ratioY);

    //// Equality.
    //bool operator==(Vector3f* const& right) const;

    //bool operator!=(Vector3f* const& right) const;

    //// Add.
    //Vector3f* operator+(Vector3f* right) const;

    //Vector3f* operator+(int right) const;

    //Vector3f* operator+(float right) const;

    //// Subtract.
    //Vector3f* operator-(Vector3f* right) const;

    //Vector3f* operator-(int right) const;

    //Vector3f* operator-(float right) const;

    //// Multiply.
    //Vector3f* operator*(Vector3f* right) const;

    //Vector3f* operator*(int scalar) const;
    //Vector3f* operator*(float scalar) const;

    //// Divide.
    //Vector3f* operator/(Vector3f* right) const;

    //Vector3f* operator/(int scalar) const;
    //Vector3f* operator/(float scalar) const;

    static Vector3f* Add(Vector3f* left, Vector3f* right);

    static Vector3f* Add(Vector3f* left, int offset);

    static Vector3f* Subtract(Vector3f* left, Vector3f* right);

    static Vector3f* Subtract(Vector3f* left, int subtractant);

    static Vector3f* Multiply(Vector3f* left, Vector3f* right); // Not particularly mathematically correct yet still useful as dont know if to do a Dot Product or Cross Product

    static Vector3f* Scale(Vector3f* left, float scalar);

    static Vector3f* Scale(Vector3f* left, int scalar);

    static Vector3f* Divide(Vector3f* left, Vector3f* right);

    static Vector3f* Divide(Vector3f* left, int scalar);

    //operator Vector2i* () const {
    //    Vector2i* result;
    //    result = new Vector2i((int)this->x, (int)this->y);
    //    return result;
    //}

    //operator Vector2f* () const {
    //    Vector2f* result;
    //    result = new Vector2f((float)this->x, (float)this->y);
    //    return result;
    //}

    //operator Vector3f* () const {
    //    Vector3f* result;
    //    result = new Vector3f(this->x, this->y, this->z);
    //    return result;
    //}

    //operator Vector4f* () const {
    //    Vector4f* result;
    //    result = new Vector4f(this->x, this->y, this->z, 0.0f);
    //    return result;
    //}
};


#endif