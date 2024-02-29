#include <cmath>

#include "Vector2f.h"
//#include "Vector2i.h"
//#include "Vector3f.h"
//#include "Vector4f.h"
//#include "VectorLib.h"



//Vector2f::Vector2f() 
//{
//	this->x = 0.0f;
//	this->y = 0.0f;
//}
//Vector2f::Vector2f(float _x, float _y)
//{
//	this->x = _x;
//	this->y = _y;
//}
//Vector2f::Vector2f(int _x, int _y)
//{
//	this->x = (float)x;
//	this->y = (float)y;
//}
Vector2f* Vector2f::xy()
{
	Vector2f* result;
	result = new Vector2f(x, y);
	return result;
}
void Vector2f::xy(Vector2f* value)
{
	this->x = value->x;
	this->y = value->y;
}
Vector3f* Vector2f::xyz()
{
	Vector3f* result;
	result = new Vector3f(x, y, 0.0f);
	return result;
}
void Vector2f::xyz(Vector3f* value)
{
	this->x = value->x;
	this->y = value->y;
}
Vector4f* Vector2f::xyzw()
{
	Vector4f* result;
	result = new Vector4f(x, y, 0.0f, 0.0f);
	return result;
}
void Vector2f::xyzw(Vector4f* value)
{
	this->x = value->x;
	this->y = value->y;
}
Vector2f* Vector2f::Normalised()
{
	return Normalise();
}

float Vector2f::MagnitudeSquared()
{
	float length = sqrt((x * x) + (y * y));
	return length;
}

float Vector2f::Magnitude()
{
	return (x * x) + (y * y);
}

Vector2f* Vector2f::Normalise()
{
	Vector2f* result;
	float magnitude = MagnitudeSquared();
	result = new Vector2f(x / magnitude, y / magnitude);
	return result;
}

//float Vector2f::Dot(Vector2f* left, Vector2f* right)
//{
//	return (left->x * right->x) + (left->y * right->y);
//}

float Vector2f::Cross(Vector2f* left, Vector2f* right)
{
	return (left->x * right->y) - (right->x * left->y);
}

float Vector2f::Lerp(float from, float to, float ratio)
{
	return from + ((to - from) * ratio);
}

Vector2f* Vector2f::Lerp(Vector2f* from, Vector2f* to, float ratio)
{
	Vector2f* result;
	result = new Vector2f(from->x + ((to->x - from->x) * ratio), from->y + ((to->y - from->y) * ratio));
	return result;
}

Vector2f* Vector2f::TriangleLerp(Vector2f* a, Vector2f* b, Vector2f* c, float ratioX, float ratioY)
{
	Vector2f* result;
	result = new Vector2f(a->x + ((b->x - a->x) * ratioX) + ((c->x - a->x) * ratioY), a->y + ((b->y - a->y) * ratioX) + ((c->y - a->y) * ratioY));
	return result;
}

Vector2f* Vector2f::BarycetricInterpolator(Vector2f* a, Vector2f* b, Vector2f* c, float ratioX, float ratioY)
{
	return TriangleLerp(a, b, c, ratioX, ratioY);
}

float* Vector2f::ToArray()
{
	return new float[2] {x, y};
}



//// Add.
//Vector2f* Vector2f::operator+(Vector2f* right) const {
//	Vector2f* result;
//	result = new Vector2f(this->x + right->x, this->y + right->y);
//	return result;
//}
//
//Vector2f* Vector2f::operator+(int right) const {
//	Vector2f* result;
//	result = new Vector2f(this->x + right, this->y + right);
//	return result;
//}
//
//Vector2f* Vector2f::operator+(float right) const {
//	Vector2f* result;
//	result = new Vector2f((int)(this->x + right), (int)(this->y + right));
//	return result;
//}
//
//// Subtract.
//Vector2f* Vector2f::operator-(Vector2f* right) const {
//	Vector2f* result;
//	result = new Vector2f(this->x - right->x, this->y - right->y);
//	return result;
//}
//
//Vector2f* Vector2f::operator-(int right) const {
//	Vector2f* result;
//	result = new Vector2f(this->x - right, this->y - right);
//	return result;
//}
//
//Vector2f* Vector2f::operator-(float right) const {
//	Vector2f* result;
//	result = new Vector2f((int)(this->x - right), (int)(this->y - right));
//	return result;
//}

//// Multiply.
//Vector2f* Vector2f::operator*(Vector2f* right) const {
//	Vector2f* result;
//	result = new Vector2f(this->x * right->x, this->y * right->y);
//	return result;
//}
//
//Vector2f* Vector2f::operator*(int scalar) const {
//	Vector2f* result;
//	result = new Vector2f(this->x * scalar, this->y * scalar);
//	return result;
//}
//
//Vector2f* Vector2f::operator*(float scalar) const {
//	Vector2f* result;
//	result = new Vector2f((int)(this->x * scalar), (int)(this->y * scalar));
//	return result;
//}

//// Divide.
//Vector2f* Vector2f::operator/(Vector2f* right) const {
//	Vector2f* result;
//	result = new Vector2f(this->x / right->x, this->y / right->y);
//	return result;
//}
//
//Vector2f* Vector2f::operator/(int scalar) const {
//	Vector2f* result;
//	result = new Vector2f(this->x / scalar, this->y / scalar);
//	return result;
//}
//
//Vector2f* Vector2f::operator/(float scalar) const {
//	Vector2f* result;
//	result = new Vector2f((int)(this->x / scalar), (int)(this->y / scalar));
//	return result;
//}

Vector2f* Vector2f::Add(Vector2f* left, Vector2f* right)
{
	Vector2f* result;
	result = new Vector2f(left->x + right->x, left->y + right->y);
	return result;
}

Vector2f* Vector2f::Add(Vector2f* left, int offset)
{
	Vector2f* result;
	result = new Vector2f(left->x + offset, left->y + offset);
	return result;
}

Vector2f* Vector2f::Subtract(Vector2f* left, Vector2f* right)
{
	Vector2f* result;
	result = new Vector2f(left->x - right->x, left->y - right->y);
	return result;
}

Vector2f* Vector2f::Subtract(Vector2f* left, int scalar)
{
	Vector2f* result;
	result = new Vector2f(left->x - scalar, left->y - scalar);
	return result;
}

Vector2f* Vector2f::Multiply(Vector2f* left, Vector2f* right) // Not particularly mathematically correct yet still useful as dont know if to do a Dot Product or Cross Product
{
	Vector2f* result;
	result = new Vector2f(left->x * right->x, left->y * right->y);
	return result;
}

Vector2f* Vector2f::Scale(Vector2f* left, float scalar)
{
	Vector2f* result;
	result = new Vector2f((int)(left->x * scalar), (int)(left->y * scalar));
	return result;
}

Vector2f* Vector2f::Scale(Vector2f* left, int scalar)
{
	Vector2f* result;
	result = new Vector2f(left->x * scalar, left->y * scalar);
	return result;
}

Vector2f* Vector2f::Divide(Vector2f* left, Vector2f* right)
{
	Vector2f* result;
	result = new Vector2f(left->x / right->x, left->y / right->y); // TODO: could optimise these divides by multiplying by 1 / component
	return result;
}

Vector2f* Vector2f::Divide(Vector2f* left, int scalar)
{
	Vector2f* result;
	result = new Vector2f(left->x / scalar, left->y / scalar);
	return result;
}