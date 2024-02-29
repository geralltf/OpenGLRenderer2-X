#include "Vector2i.h"

Vector2i* Vector2i::ZERO = new Vector2i(0, 0);
Vector2i* Vector2i::ONE = new Vector2i(1, 1);
Vector2i* Vector2i::UnitX = new Vector2i(1, 0);
Vector2i* Vector2i::UnitY = new Vector2i(0, 1);

Vector2i::Vector2i()
{
    x = 0;
    y = 0;
}
Vector2i::Vector2i(int x, int y) {
    this->x = x;
    this->y = y;
}
Vector2i::Vector2i(float x, float y) {
    this->x = (int)x;
    this->y = (int)y;
}
Vector2i* Vector2i::xyi()
{
    Vector2i* result;
    result = new Vector2i(x, y);
    return result;
}
void Vector2i::xyi(Vector2i* value)
{
    this->x = value->x;
    this->y = value->y;
}
Vector2f* Vector2i::xy()
{
    Vector2f* result;
    result = new Vector2f(x, y);
    return result;
}
void Vector2i::xy(Vector2f* value)
{
    this->x = (int)value->x;
    this->y = (int)value->y;
}
Vector3f* Vector2i::xyz()
{
    Vector3f* result = new Vector3f((float)x, (float)y, 0.0f);
    return result;
}
void Vector2i::xyz(Vector3f* value)
{
    this->x = (int)value->x;
    this->y = (int)value->y;
}
Vector4f* Vector2i::xyzw()
{
    Vector4f* result = new Vector4f(x, y, 0.0f, 0.0f);
    return result;
}
void Vector2i::xyzw(Vector4f* value)
{
    this->x = (int)value->x;
    this->y = (int)value->y;
}

//Vector2i::Vector2i(int X, int Y)
//{
//    this->x = X;
//    this->y = Y;
//}
//
//Vector2i::Vector2i(float X, float Y)
//{
//    this->x = (int)X;
//    this->y = (int)Y;
//}

float Vector2i::MagnitudeSquared()
{
    return sqrt((x * x) + (y * y));
}

float Vector2i::Magnitude()
{
    return (x * x) + (y * y);
}

float Vector2i::Dot(Vector2f* left, Vector2f* right)
{
    return (left->x * right->x) + (left->y * right->y);
}

float Vector2i::Cross(Vector2f* left, Vector2f* right)
{
    return (left->x * right->y) - (right->x * left->y);
}

float Vector2i::Lerp(float from, float to, float ratio)
{
    return from + ((to - from) * ratio);
}

Vector2i* Vector2i::Lerp(Vector2i* from, Vector2i* to, float ratio)
{
    Vector2i* result;
    result = new Vector2i(from->x + ((to->x - from->x) * ratio), from->y + ((to->y - from->y) * ratio));
    return result;
}

Vector2i* Vector2i::TriangleLerp(Vector2i* a, Vector2i* b, Vector2i* c, float ratioX, float ratioY)
{
    Vector2i* result;
    result = new Vector2i(a->x + ((b->x - a->x) * ratioX) + ((c->x - a->x) * ratioY), a->y + ((b->y - a->y) * ratioX) + ((c->y - a->y) * ratioY));
    return result;
}

Vector2i* Vector2i::BarycetricInterpolator(Vector2i* a, Vector2i* b, Vector2i* c, float ratioX, float ratioY)
{
    return TriangleLerp(a, b, c, ratioX, ratioY);
}

//// Equality.
//bool Vector2i::operator==(Vector2i* const& right) const {
//    return is_equal(this->x, right->x) && is_equal(this->y, right->y);
//}
//
//bool Vector2i::operator!=(Vector2i* const& right) const {
//    return !is_equal(this->x, right->x) || !is_equal(this->y, right->y);
//}
//
//// Add.
//Vector2i* Vector2i::operator+(Vector2i* right) const {
//    Vector2i* result;
//    result = new Vector2i(this->x + right->x, this->y + right->y);
//    return result;
//}
//
//Vector2i* Vector2i::operator+(int right) const {
//    Vector2i* result;
//    result = new Vector2i(this->x + right, this->y + right);
//    return result;
//}
//
//Vector2i* Vector2i::operator+(float right) const {
//    Vector2i* result;
//    result = new Vector2i((int)(this->x + right), (int)(this->y + right));
//    return result;
//}
//
//// Subtract.
//Vector2i* Vector2i::operator-(Vector2i* right) const {
//    Vector2i* result;
//    result = new Vector2i(this->x - right->x, this->y - right->y);
//    return result;
//}
//
//Vector2i* Vector2i::operator-(int right) const {
//    Vector2i* result;
//    result = new Vector2i(this->x - right, this->y - right);
//    return result;
//}
//
//Vector2i* Vector2i::operator-(float right) const {
//    Vector2i* result;
//    result = new Vector2i((int)(this->x - right), (int)(this->y - right));
//    return result;
//}
//
//// Multiply.
//Vector2i* Vector2i::operator*(Vector2i* right) const {
//    Vector2i* result;
//    result = new Vector2i(this->x * right->x, this->y * right->y);
//    return result;
//}
//
//Vector2i* Vector2i::operator*(int scalar) const {
//    Vector2i* result;
//    result = new Vector2i(this->x * scalar, this->y * scalar);
//    return result;
//}
//
//Vector2i* Vector2i::operator*(float scalar) const {
//    Vector2i* result;
//    result = new Vector2i((int)(this->x * scalar), (int)(this->y * scalar));
//    return result;
//}
//
//// Divide.
//Vector2i* Vector2i::operator/(Vector2i* right) const {
//    Vector2i* result;
//    result = new Vector2i(this->x / right->x, this->y / right->y);
//    return result;
//}
//
//Vector2i* Vector2i::operator/(int scalar) const {
//    Vector2i* result;
//    result = new Vector2i(this->x / scalar, this->y / scalar);
//    return result;
//}
//
//Vector2i* Vector2i::operator/(float scalar) const {
//    Vector2i* result;
//    result = new Vector2i((int)(this->x / scalar), (int)(this->y / scalar));
//    return result;
//}

Vector2i* Vector2i::Add(Vector2i* left, Vector2i* right)
{
    Vector2i* result;
    result = new Vector2i(left->x + right->x, left->y + right->y);
    return result;
}

Vector2i* Vector2i::Add(Vector2i* left, int offset)
{
    Vector2i* result;
    result = new Vector2i(left->x + offset, left->y + offset);
    return result;
}

Vector2i* Vector2i::Subtract(Vector2i* left, Vector2i* right)
{
    Vector2i* result;
    result = new Vector2i(left->x - right->x, left->y - right->y);
    return result;
}

Vector2i* Vector2i::Subtract(Vector2i* left, int scalar)
{
    Vector2i* result;
    result = new Vector2i(left->x - scalar, left->y - scalar);
    return result;
}

Vector2i* Vector2i::Multiply(Vector2i* left, Vector2i* right) // Not particularly mathematically correct as dont know if to do a Dot Product or Cross Product
{
    Vector2i* result;
    result = new Vector2i(left->x * right->x, left->y * right->y);
    return result;
}

Vector2i* Vector2i::Scale(Vector2i* left, float scalar)
{
    Vector2i* result;
    result = new Vector2i((int)(left->x * scalar), (int)(left->y * scalar));
    return result;
}

Vector2i* Vector2i::Scale(Vector2i* left, int scalar)
{
    Vector2i* result;
    result = new Vector2i(left->x * scalar, left->y * scalar);
    return result;
}

Vector2i* Vector2i::Divide(Vector2i* left, Vector2i* right)
{
    Vector2i* result;
    result = new Vector2i(left->x / right->x, left->y / right->y); // TODO: could optimise these divides by multiplying by 1 / component
    return result;
}

Vector2i* Vector2i::Divide(Vector2i* left, int scalar)
{
    Vector2i* result;
    result = new Vector2i(left->x / scalar, left->y / scalar);
    return result;
}