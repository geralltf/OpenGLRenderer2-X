#ifndef VECTOR4F_H
#define VECTOR4F_H


#include "Vector3f.h"
#include "VectorLib.h"
#include "Vector2i.h"
#include "Vector2f.h"


//class Vector2i;
////class Vector3f;
//class Vector2f;
//class Vector4f;
//class Matrix4;
//class Quaternion;

class Vector4f
{
public:
    static Vector4f* ZERO;
    static Vector4f* ONE;
    static Vector4f* Forward;
    static Vector4f* Back;
    static Vector4f* Left;
    static Vector4f* Right;
    static Vector4f* Up;
    static Vector4f* Down;
    static Vector4f* UnitX;
    static Vector4f* UnitY;
    static Vector4f* UnitZ;
    static Vector4f* UnitW;

    float x;
    float y;
    float z;
    float w;

    Vector4f();

    Vector4f(float x, float y, float z, float w);

    Vector4f(Vector3f* value);

    Vector4f(Vector3f* value, float w);

    Vector2i* xyi();
    void xyi(Vector2i* value);

    Vector2f* xy();
    void xy(Vector2f* value);
    Vector3f* xyz();
    void xyz(Vector3f* value);

    Vector4f* xyzw();
    void xyzw(Vector4f* value);

    Vector3f* xyw();

    void xyw(Vector3f* value);

    Vector4f* Normalised();
    float MagnitudeSquared();

    float Magnitude();

    Vector4f* PerspectiveDivide();

    Vector4f* Normalise();

    float GetMagnitudeSquared();

    float GetMagnitude();

    float Combine();

    Vector4f* TransformVector(Matrix4* transformationMatrix);

    static float Dot(Vector4f* left, Vector4f* right);

    static float Dot(Vector4f* left, Vector3f* right);

    static Vector4f* Lerp(Vector4f* from, Vector4f* to, float ratio);

    static Vector4f* TriangleLerp(Vector4f* a, Vector4f* b, Vector4f* c, float ratioX, float ratioY);

    static Vector4f* BarycetricInterpolator(Vector4f* a, Vector4f* b, Vector4f* c, float ratioX, float ratioY);

    float* ToArray();

    //bool operator==(Vector3f* const& right) const {
    //    return is_equal(this->x, right->x) && is_equal(this->y, right->y) && is_equal(this->z, right->z);
    //}

    //bool operator!=(Vector3f* const& right) const {
    //    return !is_equal(this->x, right->x) || !is_equal(this->y, right->y) || !is_equal(this->z, right->z);
    //}

    //// Add.
    //Vector4f* operator+(Vector4f* right) const {
    //    Vector4f* result;
    //    result = new Vector4f(this->x + right->x, this->y + right->y, this->z + right->z, this->w + right->w);
    //    return result;
    //}

    //Vector3f* operator+(int right) const {
    //    Vector3f* result;
    //    result = new Vector3f(this->x + right, this->y + right, this->z + right);
    //    return result;
    //}

    //Vector3f* operator+(float right) const {
    //    Vector3f* result;
    //    result = new Vector3f((this->x + right), (this->y + right), (this->z + right));
    //    return result;
    //}

    //// Subtract.
    //Vector3f* operator-(Vector3f* right) const {
    //    Vector3f* result;
    //    result = new Vector3f(this->x - right->x, this->y - right->y, this->z - right->z);
    //    return result;
    //}

    //Vector3f* operator-(int right) const {
    //    Vector3f* result;
    //    result = new Vector3f(this->x - right, this->y - right, this->z - right);
    //    return result;
    //}

    //Vector3f* operator-(float right) const {
    //    Vector3f* result;
    //    result = new Vector3f(this->x - right, this->y - right, this->z - right);
    //    return result;
    //}

    //// Multiply.
    //Vector3f* operator*(Vector3f* right) const {
    //    Vector3f* result;
    //    result = new Vector3f(this->x * right->x, this->y * right->y, this->z * right->z);
    //    return result;
    //}

    //Vector3f* operator*(int scalar) const {
    //    Vector3f* result;
    //    result = new Vector3f(this->x * scalar, this->y * scalar, this->z * scalar);
    //    return result;
    //}

    //Vector3f* operator*(float scalar) const {
    //    Vector3f* result;
    //    result = new Vector3f(this->x * scalar, this->y * scalar, this->z * scalar);
    //    return result;
    //}

    //// Divide.
    //Vector3f* operator/(Vector3f* right) const {
    //    Vector3f* result;
    //    result = new Vector3f(this->x / right->x, this->y / right->y, this->z / right->z);
    //    return result;
    //}

    //Vector3f* operator/(int scalar) const {
    //    Vector3f* result;
    //    result = new Vector3f(this->x / scalar, this->y / scalar, this->z / scalar);
    //    return result;
    //}

    //Vector3f* operator/(float scalar) const {
    //    Vector3f* result;
    //    result = new Vector3f(this->x / scalar, this->y / scalar, this->z / scalar);
    //    return result;
    //}

    static Vector3f* Add(Vector3f* left, Vector3f* right);

    static Vector3f* Add(Vector3f* left, int offset);

    static Vector4f* Subtract(Vector4f* left, Vector4f* right);

    static Vector4f* Subtract(Vector4f* left, int subtractant);

    static Vector3f* Subtract(Vector3f* left, Vector3f* right);

    static Vector3f* Subtract(Vector3f* left, int subtractant);

    static Vector3f* Multiply(Vector3f* left, Vector3f* right); // Not particularly mathematically correct yet still useful as dont know if to do a Dot Product or Cross Product


    static Vector4f* Multiply(Vector4f* left, Vector4f* right); // Not particularly mathematically correct yet still useful as dont know if to do a Dot Product or Cross Product

    static Vector3f* Scale(Vector3f* left, float scalar);

    static Vector3f* Scale(Vector3f* left, int scalar);


    static Vector4f* Scale(Vector4f* left, Vector4f* scalar);

    static Vector4f* Scale(Vector4f* left, float scalar);

    static Vector4f* Scale(Vector4f* left, int scalar);

    static Vector4f* Add(Vector4f* left, Vector4f* scalar);

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
    //    result = new Vector4f(this->x, this->y, this->z, this->w);
    //    return result;
    //}
};


#endif