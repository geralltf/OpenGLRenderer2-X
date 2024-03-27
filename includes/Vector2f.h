#ifndef VECTOR2F_H
#define VECTOR2F_H

class Vector2i;
class Vector3f;
//class Vector2f;
class Vector4f;
class Matrix4;
class Quaternion;

#include "VectorLib.h"
#include "Vector2i.h"
#include "Vector3f.h"
#include "Vector4f.h"

class Vector2i;
class Vector3f;
//class Vector2f;
class Vector4f;
class Matrix4;
class Quaternion;
class Vector2f;

//static Vector2f* ZERO;
//static Vector2f* ONE;
//static Vector2f* UnitX;
//static Vector2f* UnitY;


class Vector2f
{
public:

    float x;
    float y;

    //Vector2f();
    //Vector2f(float _x, float _y);
    //Vector2f(int _x, int _y);
    Vector2f()
    {
        this->x = 0.0f;
        this->y = 0.0f;
    }
    Vector2f(float _x, float _y)
    {
        this->x = _x;
        this->y = _y;
    }
    Vector2f(int _x, int _y)
    {
        this->x = (float)x;
        this->y = (float)y;
    }
    Vector2f(unsigned int _x, unsigned int _y)
    {
        this->x = (float)x;
        this->y = (float)y;
    }
    Vector2f* xy();
    void xy(Vector2f* value);
    Vector3f* xyz();
    void xyz(Vector3f* value);
    Vector4f* xyzw();
    void xyzw(Vector4f* value);
    Vector2f* Normalised();

    float MagnitudeSquared();

    float Magnitude();

    Vector2f* Normalise();

    //static float Dot(Vector2f* left, Vector2f* right);
    static float Dot(Vector2f* left, Vector2f* right)
    {
        return (left->x * right->x) + (left->y * right->y);
    }

    static float Cross(Vector2f* left, Vector2f* right);

    static float Lerp(float from, float to, float ratio);

    static Vector2f* Lerp(Vector2f* from, Vector2f* to, float ratio);

    static Vector2f* TriangleLerp(Vector2f* a, Vector2f* b, Vector2f* c, float ratioX, float ratioY);
    static Vector2f* BarycetricInterpolator(Vector2f* a, Vector2f* b, Vector2f* c, float ratioX, float ratioY);
    
    float* ToArray();

    // Equality.
    bool operator==(Vector2f* const& right) const;

    bool operator!=(Vector2f* const& right) const;

    // Add.
    Vector2f* operator+(Vector2f* right) const;

    Vector2f* operator+(int right) const;

    Vector2f* operator+(float right) const;

    // Subtract.
    Vector2f* operator-(Vector2f* right) const;

    Vector2f* operator-(int right) const;

    Vector2f* operator-(float right) const;

    //// Multiply.
    //Vector2f* operator*(Vector2f* right);

    //Vector2f* operator*(int scalar);

    //Vector2f* operator*(float scalar);

    //// Divide.
    //Vector2f* operator/(Vector2f* right);

    //Vector2f* operator/(int scalar);

    //Vector2f* operator/(float scalar);

    static Vector2f* Add(Vector2f* left, Vector2f* right);

    static Vector2f* Add(Vector2f* left, int offset);

    static Vector2f* Subtract(Vector2f* left, Vector2f* right);

    static Vector2f* Subtract(Vector2f* left, int scalar);

    static Vector2f* Multiply(Vector2f* left, Vector2f* right); // Not particularly mathematically correct yet still useful as dont know if to do a Dot Product or Cross Product

    static Vector2f* Scale(Vector2f* left, float scalar);

    static Vector2f* Scale(Vector2f* left, int scalar);

    static Vector2f* Divide(Vector2f* left, Vector2f* right);

    static Vector2f* Divide(Vector2f* left, int scalar);

    //operator Vector2f* () const {
    //    Vector2f* result;
    //    result = new Vector2f((float)this->x, (float)this->y);
    //    return result;
    //}

    //operator Vector3f* () const {
    //    Vector3f* result;
    //    result = new Vector3f((float)this->x, (float)this->y, 0.0f);
    //    return result;
    //}

    //operator Vector4f* () const {
    //    Vector4f* result;
    //    result = new Vector4f((float)this->x, (float)this->y, 0.0f, 0.0f);
    //    return result;
    //}
};

static Vector2f* Vector2f_ZERO = new Vector2f(0.0f, 0.0f);
static Vector2f* Vector2f_ONE = new Vector2f(1.0f, 1.0f);
static Vector2f* Vector2f_UnitX = new Vector2f(1.0f, 0.0f);
static Vector2f* Vector2f_UnitY = new Vector2f(0.0f, 1.0f);

//// Equality.
//bool Vector2f::operator==(Vector2f* const& right) const {
//    return is_equal(this->x, right->x) && is_equal(this->y, right->y);
//}
//
//bool Vector2f::operator!=(Vector2f* const& right) const {
//    return !is_equal(this->x, right->x) || !is_equal(this->y, right->y);
//}

#endif