#include "Vector4f.h"

Vector4f* Vector4f::ZERO = new Vector4f(0.0f, 0.0f, 0.0f, 0.0f);
Vector4f* Vector4f::ONE = new Vector4f(1.0f, 1.0f, 1.0f, 0.0f);
Vector4f* Vector4f::Forward = new Vector4f(0.0f, 0.0f, 1.0f, 0.0f);
Vector4f* Vector4f::Back = new Vector4f(0.0f, 0.0f, -1.0f, 0.0f);
Vector4f* Vector4f::Left = new Vector4f(-1.0f, 0.0f, 0.0f, 0.0f);
Vector4f* Vector4f::Right = new Vector4f(1.0f, 0.0f, 0.0f, 0.0f);
Vector4f* Vector4f::Up = new Vector4f(0.0f, 1.0f, 0.0f, 0.0f);
Vector4f* Vector4f::Down = new Vector4f(0.0f, -1.0f, 0.0f, 0.0f);
Vector4f* Vector4f::UnitX = new Vector4f(1.0f, 0.0f, 0.0f, 0.0f);
Vector4f* Vector4f::UnitY = new Vector4f(0.0f, 1.0f, 0.0f, 0.0f);
Vector4f* Vector4f::UnitZ = new Vector4f(0.0f, 0.0f, 1.0f, 0.0f);
Vector4f* Vector4f::UnitW = new Vector4f(0.0f, 0.0f, 1.0f, 0.0f);

Vector4f::Vector4f() {
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 0.0f;
}

Vector4f::Vector4f(float x, float y, float z, float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vector4f::Vector4f(Vector3f* value)
{
	x = value->x;
	y = value->y;
	z = value->z;
}

Vector4f::Vector4f(Vector3f* value, float w)
{
	this->x = value->x;
	this->y = value->y;
	this->z = value->z;
	this->w = w;
}

Vector2i* Vector4f::xyi()
{
	Vector2i* result;
	result = new Vector2i((int)this->x, (int)this->y);
	return result;
}
void Vector4f::xyi(Vector2i* value)
{
	this->x = (float)value->x;
	this->y = (float)value->y;
}

Vector2f* Vector4f::xy()
{
	Vector2f* result;
	result = new Vector2f(this->x, this->y);
	return result;
}
void Vector4f::xy(Vector2f* value)
{
	this->x = value->x;
	this->y = value->y;
}

Vector3f* Vector4f::xyz()
{
	Vector3f* result;
	result = new Vector3f(this->x, this->y, this->z);
	return result;
}
void Vector4f::xyz(Vector3f* value)
{
	this->x = value->x;
	this->y = value->y;
	this->z = value->z;
}

Vector4f* Vector4f::xyzw()
{
	Vector4f* result;
	result = new Vector4f(this->x, this->y, this->z, 0.0f);
	return result;
}
void Vector4f::xyzw(Vector4f* value)
{
	this->x = value->x;
	this->y = value->y;
	this->z = value->z;
}

Vector3f* Vector4f::xyw()
{
	Vector3f* result;
	result = new Vector3f(this->x, this->y, this->w);
	return result;
}

void Vector4f::xyw(Vector3f* value)
{
	this->x = value->x;
	this->y = value->y;
	this->w = value->z;
}

Vector4f* Vector4f::Normalised()
{
	return Normalise();
}

float Vector4f::MagnitudeSquared()
{
	float length = sqrt((x * x) + (y * y) + (z * z) + (w * w));
	return length;
}

float Vector4f::Magnitude()
{
	float length_approximated = (x * x) + (y * y) + (z * z) + (w * w);
	return length_approximated;
}

Vector4f* Vector4f::PerspectiveDivide()
{
	Vector4f* fake_perspective_projection;
	fake_perspective_projection = new Vector4f(this->x / this->w, this->y / this->w, this->z / this->w, this->w);
	return fake_perspective_projection;
}

Vector4f* Vector4f::Normalise()
{
	Vector4f* normalised_result;
	float magnitude = MagnitudeSquared();
	normalised_result = new Vector4f(x / magnitude, y / magnitude, z / magnitude, w / magnitude);
	return normalised_result;
}

float Vector4f::GetMagnitudeSquared()
{
	float length = sqrt((x * x) + (y * y) + (z * z) + (w * w));
	return length;
}

float Vector4f::GetMagnitude()
{
	float length_approximated = (x * x) + (y * y) + (z * z) + (w * w);
	return length_approximated;
}

float Vector4f::Combine()
{
	return x * y * z * w;
}

Vector4f* Vector4f::TransformVector(Matrix4* transformationMatrix)
{
	return Matrix4::TransformVector(transformationMatrix, this);
	//return transformationMatrix * this;
}

float Vector4f::Dot(Vector4f* left, Vector4f* right)
{
	return (left->x * right->x)
		+ (left->y * right->y)
		+ (left->z * right->z)
		+ (left->w * right->w);
}

float Vector4f::Dot(Vector4f* left, Vector3f* right)
{
	return (left->x * right->x)
		+ (left->y * right->y)
		+ (left->z * right->z)
		+ (left->w * 1.0f); // Unsure if w should be same.
}

Vector4f* Vector4f::Lerp(Vector4f* from, Vector4f* to, float ratio)
{
	Vector4f* result;

	result = new Vector4f(
		from->x + ((to->x - from->x) * ratio),
		from->y + ((to->y - from->y) * ratio),
		from->z + ((to->z - from->z) * ratio),
		from->w + ((to->w - from->w) * ratio)
	);

	return result;
}

Vector4f* Vector4f::TriangleLerp(Vector4f* a, Vector4f* b, Vector4f* c, float ratioX, float ratioY)
{
	Vector4f* result;

	result = new Vector4f(
		a->x + ((b->x - a->x) * ratioX) + ((c->x - a->x) * ratioY),
		a->y + ((b->y - a->y) * ratioX) + ((c->y - a->y) * ratioY),
		a->z + ((b->z - a->z) * ratioX) + ((c->z - a->z) * ratioY),
		a->w + ((b->w - a->w) * ratioX) + ((c->w - a->w) * ratioY)
	);

	return result;
}

Vector4f* Vector4f::BarycetricInterpolator(Vector4f* a, Vector4f* b, Vector4f* c, float ratioX, float ratioY)
{
	return TriangleLerp(a, b, c, ratioX, ratioY);
}

float* Vector4f::ToArray()
{
	return new float[4] {x, y, z, w};
}

//bool Vector4f::operator==(Vector3f* const& right) const {
//	return is_equal(this->x, right->x) && is_equal(this->y, right->y) && is_equal(this->z, right->z);
//}
//
//bool Vector4f::operator!=(Vector3f* const& right) const {
//	return !is_equal(this->x, right->x) || !is_equal(this->y, right->y) || !is_equal(this->z, right->z);
//}
//
//// Add.
//Vector4f* Vector4f::operator+(Vector4f* right) const {
//	Vector4f* result;
//	result = new Vector4f(this->x + right->x, this->y + right->y, this->z + right->z, this->w + right->w);
//	return result;
//}
//
//Vector3f* Vector4f::operator+(int right) const {
//	Vector3f* result;
//	result = new Vector3f(this->x + right, this->y + right, this->z + right);
//	return result;
//}
//
//Vector3f* Vector4f::operator+(float right) const {
//	Vector3f* result;
//	result = new Vector3f((this->x + right), (this->y + right), (this->z + right));
//	return result;
//}
//
//// Subtract.
//Vector3f* Vector4f::operator-(Vector3f* right) const {
//	Vector3f* result;
//	result = new Vector3f(this->x - right->x, this->y - right->y, this->z - right->z);
//	return result;
//}
//
//Vector3f* Vector4f::operator-(int right) const {
//	Vector3f* result;
//	result = new Vector3f(this->x - right, this->y - right, this->z - right);
//	return result;
//}
//
//Vector3f* Vector4f::operator-(float right) const {
//	Vector3f* result;
//	result = new Vector3f(this->x - right, this->y - right, this->z - right);
//	return result;
//}
//
//// Multiply.
//Vector3f* Vector4f::operator*(Vector3f* right) const {
//	Vector3f* result;
//	result = new Vector3f(this->x * right->x, this->y * right->y, this->z * right->z);
//	return result;
//}
//
//Vector3f* Vector4f::operator*(int scalar) const {
//	Vector3f* result;
//	result = new Vector3f(this->x * scalar, this->y * scalar, this->z * scalar);
//	return result;
//}
//
//Vector3f* Vector4f::operator*(float scalar) const {
//	Vector3f* result;
//	result = new Vector3f(this->x * scalar, this->y * scalar, this->z * scalar);
//	return result;
//}
//
//// Divide.
//Vector3f* Vector4f::operator/(Vector3f* right) const {
//	Vector3f* result;
//	result = new Vector3f(this->x / right->x, this->y / right->y, this->z / right->z);
//	return result;
//}
//
//Vector3f* Vector4f::operator/(int scalar) const {
//	Vector3f* result;
//	result = new Vector3f(this->x / scalar, this->y / scalar, this->z / scalar);
//	return result;
//}
//
//Vector3f* Vector4f::operator/(float scalar) const {
//	Vector3f* result;
//	result = new Vector3f(this->x / scalar, this->y / scalar, this->z / scalar);
//	return result;
//}

Vector3f* Vector4f::Add(Vector3f* left, Vector3f* right)
{
	Vector3f* result;
	result = new Vector3f(left->x + right->x, left->y + right->y, left->z + right->z);
	return result;
}

Vector3f* Vector4f::Add(Vector3f* left, int offset)
{
	Vector3f* result;
	result = new Vector3f(left->x + offset, left->y + offset, left->z + offset);
	return result;
}

Vector4f* Vector4f::Subtract(Vector4f* left, Vector4f* right)
{
	Vector4f* result;
	result = new Vector4f(left->x - right->x, left->y - right->y, left->z - right->z, left->w - right->w);
	return result;
}

Vector4f* Vector4f::Subtract(Vector4f* left, int subtractant)
{
	Vector4f* result;
	result = new Vector4f(left->x - subtractant, left->y - subtractant, left->z - subtractant, left->w - subtractant);
	return result;
}

Vector3f* Vector4f::Subtract(Vector3f* left, Vector3f* right)
{
	Vector3f* result;
	result = new Vector3f(left->x - right->x, left->y - right->y, left->z - right->z);
	return result;
}

Vector3f* Vector4f::Subtract(Vector3f* left, int subtractant)
{
	Vector3f* result;
	result = new Vector3f(left->x - subtractant, left->y - subtractant, left->z - subtractant);
	return result;
}

Vector3f* Vector4f::Multiply(Vector3f* left, Vector3f* right) // Not particularly mathematically correct yet still useful as dont know if to do a Dot Product or Cross Product
{
	Vector3f* result;
	result = new Vector3f(left->x * right->x, left->y * right->y, left->z * right->z);
	return result;
}

Vector4f* Vector4f::Multiply(Vector4f* left, Vector4f* right) // Not particularly mathematically correct yet still useful as dont know if to do a Dot Product or Cross Product
{
	Vector4f* result;
	result = new Vector4f(left->x * right->x, left->y * right->y, left->z * right->z, left->w * right->w);
	return result;
}

Vector3f* Vector4f::Scale(Vector3f* left, float scalar)
{
	Vector3f* result;
	result = new Vector3f(left->x * scalar, left->y * scalar, left->y * scalar);
	return result;
}

Vector3f* Vector4f::Scale(Vector3f* left, int scalar)
{
	Vector3f* result;
	result = new Vector3f(left->x * scalar, left->y * scalar, left->z * scalar);
	return result;
}

Vector4f* Vector4f::Scale(Vector4f* left, Vector4f* scalar) {
	Vector4f* result;
	result = new Vector4f(left->x * scalar->x, left->y * scalar->y, left->z * scalar->z, left->w * scalar->w);
	return result;
}

Vector4f* Vector4f::Scale(Vector4f* left, float scalar) {
	Vector4f* result;
	result = new Vector4f(left->x * scalar, left->y * scalar, left->z * scalar, left->w * scalar);
	return result;
}

Vector4f* Vector4f::Scale(Vector4f* left, int scalar) {
	Vector4f* result;
	result = new Vector4f(left->x * scalar, left->y * scalar, left->z * scalar, left->w * scalar);
	return result;
}

Vector4f* Vector4f::Add(Vector4f* left, Vector4f* scalar) {
	Vector4f* result;
	result = new Vector4f(left->x + scalar->x, left->y + scalar->y, left->z + scalar->z, left->w + scalar->w);
	return result;
}

Vector3f* Vector4f::Divide(Vector3f* left, Vector3f* right)
{
	Vector3f* result;
	result = new Vector3f(left->x / right->x, left->y / right->y, left->z / right->z); // TODO: could optimise these divides by multiplying by 1 / component
	return result;
}

Vector3f* Vector4f::Divide(Vector3f* left, int scalar)
{
	Vector3f* result;
	result = new Vector3f(left->x / scalar, left->y / scalar, left->z / scalar);
	return result;
}