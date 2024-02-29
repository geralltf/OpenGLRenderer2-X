#ifndef VECTOR2I_H
#define VECTOR2I_H

class Vector2i;
class Vector2f;
class Vector4f;
class Matrix4;
class Quaternion;
class Vector3f;

#include "VectorLib.h"
#include "Vector2f.h"
#include "Vector3f.h"
#include "Vector4f.h"

class Vector2f;

class Vector2i
{
public:
    static Vector2i* ZERO;
    static Vector2i* ONE;
    static Vector2i* UnitX;
    static Vector2i* UnitY;
    int x;
    int y;
    Vector2i();
    Vector2i(int x, int y);
    Vector2i(float x, float y);
    Vector2i* xyi();
    void xyi(Vector2i* value);
    Vector2f* xy();
    void xy(Vector2f* value);
    Vector3f* xyz();
    void xyz(Vector3f* value);
    Vector4f* xyzw();
    void xyzw(Vector4f* value);

    //Vector2i(int X, int Y);

    //Vector2i(float X, float Y);

    float MagnitudeSquared();

    float Magnitude();

    static float Dot(Vector2f* left, Vector2f* right);

    static float Cross(Vector2f* left, Vector2f* right);

    static float Lerp(float from, float to, float ratio);

    static Vector2i* Lerp(Vector2i* from, Vector2i* to, float ratio);

    static Vector2i* TriangleLerp(Vector2i* a, Vector2i* b, Vector2i* c, float ratioX, float ratioY);

    static Vector2i* BarycetricInterpolator(Vector2i* a, Vector2i* b, Vector2i* c, float ratioX, float ratioY);

    int* ToArray();

    // Equality.
    bool operator==(Vector2i* const& right) const;

    bool operator!=(Vector2i* const& right) const;

    //// Add.
    //Vector2i* operator+(Vector2i* right) const;

    //Vector2i* operator+(int right) const;

    //Vector2i* operator+(float right) const;

    //// Subtract.
    //Vector2i* operator-(Vector2i* right) const;

    //Vector2i* operator-(int right) const;

    //Vector2i* operator-(float right) const;

    //// Multiply.
    //Vector2i* operator*(Vector2i* right) const;

    //Vector2i* operator*(int scalar) const;

    //Vector2i* operator*(float scalar) const;

    //// Divide.
    //Vector2i* operator/(Vector2i* right) const;

    //Vector2i* operator/(int scalar) const;

    //Vector2i* operator/(float scalar) const;

    static Vector2i* Add(Vector2i* left, Vector2i* right);

    static Vector2i* Add(Vector2i* left, int offset);

    static Vector2i* Subtract(Vector2i* left, Vector2i* right);

    static Vector2i* Subtract(Vector2i* left, int scalar);

    static Vector2i* Multiply(Vector2i* left, Vector2i* right); // Not particularly mathematically correct as dont know if to do a Dot Product or Cross Product


    static Vector2i* Scale(Vector2i* left, float scalar);

    static Vector2i* Scale(Vector2i* left, int scalar);

    static Vector2i* Divide(Vector2i* left, Vector2i* right);

    static Vector2i* Divide(Vector2i* left, int scalar);

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


#endif