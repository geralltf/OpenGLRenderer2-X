#include "Vector3f.h"

Vector3f* Vector3f::ZERO = new Vector3f(0.0f, 0.0f, 0.0f);
Vector3f* Vector3f::ONE = new Vector3f(1.0f, 1.0f, 1.0f);
Vector3f* Vector3f::Forward = new Vector3f(0.0f, 0.0f, 1.0f);
Vector3f* Vector3f::Back = new Vector3f(0.0f, 0.0f, -1.0f);
Vector3f* Vector3f::Left = new Vector3f(-1.0f, 0.0f, 0.0f);
Vector3f* Vector3f::Right = new Vector3f(1.0f, 0.0f, 0.0f);
Vector3f* Vector3f::Up = new Vector3f(0.0f, 1.0f, 0.0f);
Vector3f* Vector3f::Down = new Vector3f(0.0f, -1.0f, 0.0f);
Vector3f* Vector3f::UnitX = new Vector3f(1.0f, 0.0f, 0.0f);
Vector3f* Vector3f::UnitY = new Vector3f(0.0f, 1.0f, 0.0f);
Vector3f* Vector3f::UnitZ = new Vector3f(0.0f, 0.0f, 1.0f);

Vector3f::Vector3f() {
	x = 0;
	y = 0;
	z = 0;
}

Vector3f::Vector3f(int x, int y, int z)
{
	this->x = (float)x;
	this->y = (float)y;
	this->z = (float)z;
}

Vector3f::Vector3f(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3f* Vector3f::Normalised()
{
	return Normalise();
}

//float Vector3f::MagnitudeSquared()
//{
//	float length = sqrt((x * x) + (y * y) + (z * z));
//	return length;
//}
//
//float Vector3f::Magnitude()
//{
//	float length_approximated = (x * x) + (y * y) + (z * z);
//	return length_approximated;
//}

Vector2f* Vector3f::xy()
{
	Vector2f* result;
	result = new Vector2f(x, y);
	return result;
}
void Vector3f::xy(Vector2f* value)
{
	this->x = value->x;
	this->y = value->y;
}
Vector3f* Vector3f::xyz()
{
	Vector3f* result;
	result = new Vector3f(x, y, z);
	return result;
}
void Vector3f::xy(Vector3f* value)
{
	this->x = value->x;
	this->y = value->y;
	this->z = value->z;
}
Vector4f* Vector3f::xyzw()
{
	Vector4f* result;
	result = new Vector4f(x, y, z, 0.0f);
	return result;
}
void Vector3f::xyzw(Vector4f* value)
{
	this->x = value->x;
	this->y = value->y;
	this->z = value->z;
}

float* Vector3f::ToArray()
{
	return new float[3]{x,y,z};
}

Vector3f* Vector3f::TransformVector(Matrix4* transformationMatrix)
{
	Vector4f* v = new Vector4f(this, 1.0f);
	Vector3f* result;
	result = Matrix4::TransformVector(transformationMatrix, v)->xyz();
	return result;
}

Vector3f* Vector3f::Add(Vector3f* v)
{
	return Add(this, v);
}

Vector3f* Vector3f::Multiply(Vector3f* value)
{
	return Multiply(this, value);
}

Vector3f* Vector3f::Scale(float scalar)
{
	return Scale(this, scalar);
}

Vector3f* Vector3f::Normalise()
{
	Vector3f* result;
	float magnitude = MagnitudeSquared();
	result = new Vector3f(x / magnitude, y / magnitude, z / magnitude);
	return result;
}

float Vector3f::MagnitudeSquared()
{
	float length = sqrt((x * x) + (y * y) + (z * z));
	return length;
}

float Vector3f::Magnitude()
{
	float length_approximated = (x * x) + (y * y) + (z * z);
	return length_approximated;
}

float Vector3f::Distance(Vector3f* source, Vector3f* target)
{
	float distance_approximated = (source->x * target->x + source->y * target->y + source->z * target->z);
	return distance_approximated;
}

float Vector3f::DistanceSquared(Vector3f* source, Vector3f* target)
{
	float distance = sqrt(source->x * target->x + source->y * target->y + source->z * target->z);
	return distance;
}

float Vector3f::Dot(Vector3f* left, Vector3f* right)
{
	return (left->x * right->x) + (left->y * right->y) + (left->z * right->z);
}

Vector3f* Vector3f::Cross(Vector3f* left, Vector3f* right)
{
	Vector3f* result;
	result = new Vector3f(
		(left->y * right->z) - (left->z * right->y),
		(left->z * right->x) - (left->x * right->z),
		(left->x * right->y) - (left->y * right->x)
	);
	return result;
}

float Vector3f::Crossf(Vector3f* left, Vector3f* right)
{
	float crossed;
	crossed = (left->y * right->z) - (left->z * right->y) -
		(left->z * right->x) - (left->x * right->z) -
		(left->x * right->y) - (left->y * right->x);
	return crossed;
}

Vector3f* Vector3f::Lerp(Vector3f* from, Vector3f* to, float ratio)
{
	Vector3f* result;
	result = new Vector3f(from->x + ((to->x - from->x) * ratio), from->y + ((to->y - from->y) * ratio), from->z + ((to->z - from->z) * ratio));
	return result;
}

Vector3f* Vector3f::TriangleLerp(Vector3f* a, Vector3f* b, Vector3f* c, float u, float v)
{
	Vector3f* result;

	float w = (1 - u - v);

	result = new Vector3f(
		(a->x + ((b->x - a->x) * u) + ((c->x - a->x) * v)),
		(a->y + ((b->y - a->y) * u) + ((c->y - a->y) * v)),
		(a->z + ((b->z - a->z) * u) + ((c->z - a->z) * v))
	);
	return result;
	//return (a + ((b - a) * u) + ((c - a) * v)); // u v

	// (1 - u - v)

	//return w*col0 + u*col1 + v*col2 where w = 1-u-v

	//return a + ((b - a) * u) + ((c - a) * v) + ((b - c) * w);

	//float invSum = 1.0f / (fAB + fBC + fCA);
	//float b1 = fBC * invSum;
	//float b2 = fCA * invSum;
	//float b3 = 1.0f - b1 - b2;
	//return a * b1 + b * b2 + c * b3;
}

Vector3f* Vector3f::BarycetricInterpolator(Vector3f* a, Vector3f* b, Vector3f* c, float ratioX, float ratioY)
{
	return TriangleLerp(a, b, c, ratioX, ratioY); // u v
}

//// Equality.
//bool Vector3f::operator==(Vector3f* const& right) const {
//	return is_equal(this->x, right->x) && is_equal(this->y, right->y) && is_equal(this->z, right->z);
//}
//
//bool Vector3f::operator!=(Vector3f* const& right) const {
//	return !is_equal(this->x, right->x) || !is_equal(this->y, right->y) || !is_equal(this->z, right->z);
//}
//
//// Add.
//Vector3f* Vector3f::operator+(Vector3f* right) const {
//	Vector3f* result;
//	result = new Vector3f(this->x + right->x, this->y + right->y, this->z + right->z);
//	return result;
//}
//
//Vector3f* Vector3f::operator+(int right) const {
//	Vector3f* result;
//	result = new Vector3f(this->x + right, this->y + right, this->z + right);
//	return result;
//}
//
//Vector3f* Vector3f::operator+(float right) const {
//	Vector3f* result;
//	result = new Vector3f((this->x + right), (this->y + right), (this->z + right));
//	return result;
//}
//
//// Subtract.
//Vector3f* Vector3f::operator-(Vector3f* right) const {
//	Vector3f* result;
//	result = new Vector3f(this->x - right->x, this->y - right->y, this->z - right->z);
//	return result;
//}
//
//Vector3f* Vector3f::operator-(int right) const {
//	Vector3f* result;
//	result = new Vector3f(this->x - right, this->y - right, this->z - right);
//	return result;
//}
//
//Vector3f* Vector3f::operator-(float right) const {
//	Vector3f* result;
//	result = new Vector3f(this->x - right, this->y - right, this->z - right);
//	return result;
//}
//
//// Multiply.
//Vector3f* Vector3f::operator*(Vector3f* right) const {
//	Vector3f* result;
//	result = new Vector3f(this->x * right->x, this->y * right->y, this->z * right->z);
//	return result;
//}
//
//Vector3f* Vector3f::operator*(int scalar) const {
//	Vector3f* result;
//	result = new Vector3f(this->x * scalar, this->y * scalar, this->z * scalar);
//	return result;
//}
//
//Vector3f* Vector3f::operator*(float scalar) const {
//	Vector3f* result;
//	result = new Vector3f(this->x * scalar, this->y * scalar, this->z * scalar);
//	return result;
//}
//
//// Divide.
//Vector3f* Vector3f::operator/(Vector3f* right) const {
//	Vector3f* result;
//	result = new Vector3f(this->x / right->x, this->y / right->y, this->z / right->z);
//	return result;
//}
//
//Vector3f* Vector3f::operator/(int scalar) const {
//	Vector3f* result;
//	result = new Vector3f(this->x / scalar, this->y / scalar, this->z / scalar);
//	return result;
//}
//
//Vector3f* Vector3f::operator/(float scalar) const {
//	Vector3f* result;
//	result = new Vector3f(this->x / scalar, this->y / scalar, this->z / scalar);
//	return result;
//}

Vector3f* Vector3f::Add(Vector3f* left, Vector3f* right)
{
	Vector3f* result;
	result = new Vector3f(left->x + right->x, left->y + right->y, left->z + right->z);
	return result;
}

Vector3f* Vector3f::Add(Vector3f* left, int offset)
{
	Vector3f* result;
	result = new Vector3f(left->x + offset, left->y + offset, left->z + offset);
	return result;
}

Vector3f* Vector3f::Subtract(Vector3f* left, Vector3f* right)
{
	Vector3f* result;
	result = new Vector3f(left->x - right->x, left->y - right->y, left->z - right->z);
	return result;
}

Vector3f* Vector3f::Subtract(Vector3f* left, int subtractant)
{
	Vector3f* result;
	result = new Vector3f(left->x - subtractant, left->y - subtractant, left->z - subtractant);
	return result;
}

Vector3f* Vector3f::Multiply(Vector3f* left, Vector3f* right) // Not particularly mathematically correct yet still useful as dont know if to do a Dot Product or Cross Product
{
	Vector3f* result;
	result = new Vector3f(left->x * right->x, left->y * right->y, left->z * right->z);
	return result;
}

Vector3f* Vector3f::Scale(Vector3f* left, float scalar)
{
	Vector3f* result;
	result = new Vector3f(left->x * scalar, left->y * scalar, left->y * scalar);
	return result;
}

Vector3f* Vector3f::Scale(Vector3f* left, int scalar)
{
	Vector3f* result;
	result = new Vector3f(left->x * scalar, left->y * scalar, left->z * scalar);
	return result;
}

Vector3f* Vector3f::Divide(Vector3f* left, Vector3f* right)
{
	Vector3f* result;
	result = new Vector3f(left->x / right->x, left->y / right->y, left->z / right->z); // TODO: could optimise these divides by multiplying by 1 / component
	return result;
}

Vector3f* Vector3f::Divide(Vector3f* left, int scalar)
{
	Vector3f* result;
	result = new Vector3f(left->x / scalar, left->y / scalar, left->z / scalar);
	return result;
}