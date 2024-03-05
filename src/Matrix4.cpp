#include "Matrix4.h"

Vector4f* Matrix4::Row0()
{
	return new Vector4f(m00, m01, m02, m03);
}
Vector4f* Matrix4::Row1()
{
	return new Vector4f(m10, m11, m12, m13);
}
Vector4f* Matrix4::Row2()
{
	return new Vector4f(m20, m21, m22, m23);
}
Vector4f* Matrix4::Row3()
{
	return new Vector4f(m30, m31, m32, m33);
}
void Matrix4::Row0(Vector4f* value)
{
	m00 = value->x;
	m01 = value->y;
	m02 = value->z;
	m03 = value->w;
}
void Matrix4::Row1(Vector4f* value)
{
	m10 = value->x;
	m11 = value->y;
	m12 = value->z;
	m13 = value->w;
}
void Matrix4::Row2(Vector4f* value)
{
	m20 = value->x;
	m21 = value->y;
	m22 = value->z;
	m23 = value->w;
}
void Matrix4::Row3(Vector4f* value)
{
	m30 = value->x;
	m31 = value->y;
	m32 = value->z;
	m33 = value->w;
}

void Matrix4::Column0(Vector4f* column0_values) {
	m00 = column0_values->x;
	m10 = column0_values->y;
	m20 = column0_values->z;
	m30 = column0_values->w;
}

void Matrix4::Column1(Vector4f* column1_values) {
	m01 = column1_values->x;
	m11 = column1_values->y;
	m21 = column1_values->z;
	m31 = column1_values->w;
}
void Matrix4::Column2(Vector4f* column2_values) {
	m02 = column2_values->x;
	m12 = column2_values->y;
	m22 = column2_values->z;
	m32 = column2_values->w;
}

void Matrix4::Column3(Vector4f* column3_value) {
	m03 = column3_value->x;
	m13 = column3_value->y;
	m23 = column3_value->z;
	m33 = column3_value->w;
}

Vector4f* Matrix4::Column0() {
	return new Vector4f(m00, m10, m20, m30);
}

Vector4f* Matrix4::Column1() {
	return new Vector4f(m01, m11, m21, m31);
}

Vector4f* Matrix4::Column2() {
	return new Vector4f(m02, m12, m22, m32);
}

Vector4f* Matrix4::Column3() {
	return new Vector4f(m03, m13, m23, m33);
}


Matrix4* Matrix4::Identity()
{
	//Matrix4* identity = new Matrix4(
	//	Vector4f::UnitX,
	//	Vector4f::UnitY,
	//	Vector4f::UnitZ,
	//	Vector4f::UnitW
	//);
	Matrix4* identity = new Matrix4(
		new Vector4f(1.0f, 0.0f, 0.0f, 0.0f),
		new Vector4f(0.0f, 1.0f, 0.0f, 0.0f),
		new Vector4f(0.0f, 0.0f, 1.0f, 0.0f),
		new Vector4f(0.0f, 0.0f, 0.0f, 1.0f)
	);
	return identity;
}

float Matrix4::Determinant()
{
	float determinant;
	Vector4f* row0 = Row0();
	Vector4f* row1 = Row1();
	Vector4f* row2 = Row2();
	Vector4f* row3 = Row3();
	determinant = (row0->x * row1->y * row2->z * row3->w) -
		(row0->x * row1->y * row2->w * row3->z) +
		(row0->x * row1->z * row2->w * row3->y) -
		(row0->x * row1->z * row2->y * row3->w) +
		(row0->x * row1->w * row2->y * row3->z) -
		(row0->x * row1->w * row2->z * row3->y) -
		(row0->y * row1->z * row2->w * row3->x) +
		(row0->y * row1->z * row2->x * row3->w) -
		(row0->y * row1->w * row2->x * row3->z) +
		(row0->y * row1->w * row2->z * row3->x) -
		(row0->y * row1->x * row2->z * row3->w) +
		(row0->y * row1->x * row2->w * row3->z) +
		(row0->z * row1->w * row2->x * row3->y) -
		(row0->z * row1->w * row2->y * row3->x) +
		(row0->z * row1->x * row2->y * row3->w) -
		(row0->z * row1->x * row2->w * row3->y) +
		(row0->z * row1->y * row2->w * row3->x) -
		(row0->z * row1->y * row2->x * row3->w) -
		(row0->w * row1->x * row2->y * row3->z) +
		(row0->w * row1->x * row2->z * row3->y) -
		(row0->w * row1->y * row2->z * row3->x) +
		(row0->w * row1->y * row2->x * row3->z) -
		(row0->w * row1->z * row2->x * row3->y) +
		(row0->w * row1->z * row2->y * row3->x);
	return determinant;
}
Matrix4* Matrix4::Inverse()
{
	Matrix4* result;

	Invert(&result);

	return result;
}

void Matrix4::Invert(Matrix4** out_result)
{
	Matrix4* result = Identity();
	float _r3x = Row3()->x;
	float _r3y = Row3()->y;
	float _r3z = Row3()->z;
	float _r3w = Row3()->w;
	float _m41 = _r3x, _m42 = _r3y, _m43 = _r3z, _m44 = _r3w;
	if (_m41 == 0 && _m42 == 0 && _m43 == 0 && _m44 == 1.0f) {
		result = InvertAffine();
		(*out_result) = result;
		return;
	}

	float d = Determinant();
	if (d == 0.0f) {
		//std::cout << "Matrix is singular and cannot be inverted." << std::endl;
		return;
	}
	float d1 = 1 / d;
	Vector4f* r0 = Row0();
	Vector4f* r1 = Row1();
	Vector4f* r2 = Row2();
	Vector4f* r3 = Row3();
	float m11 = Row0()->x, m12 = Row0()->y, m13 = Row0()->z, m14 = Row0()->w,
		m21 = Row1()->x, m22 = Row1()->y, m23 = Row1()->z, m24 = Row1()->w,
		m31 = Row2()->x, m32 = Row2()->y, m33 = Row2()->z, m34 = Row2()->w;

	float r0x = d1 * (m22 * m33 * _m44 + m23 * m34 * _m42 + m24 * m32 * _m43 - m22 * m34 * _m43 - m23 * m32 * _m44 - m24 * m33 * _m42);
	float r0y = d1 * (m12 * m34 * _m43 + m13 * m32 * _m44 + m14 * m33 * _m42 - m12 * m33 * _m44 - m13 * m34 * _m42 - m14 * m32 * _m43);
	float r0z = d1 * (m12 * m23 * _m44 + m13 * m24 * _m42 + m14 * m22 * _m43 - m12 * m24 * _m43 - m13 * m22 * _m44 - m14 * m23 * _m42);
	float r0w = d1 * (m12 * m24 * m33 + m13 * m22 * m34 + m14 * m23 * m32 - m12 * m23 * m34 - m13 * m24 * m32 - m14 * m22 * m33);
	result->Row0(new Vector4f(r0x, r0y, r0z, r0w));

	float r1x = d1 * (m21 * m34 * _m43 + m23 * m31 * _m44 + m24 * m33 * _m41 - m21 * m33 * _m44 - m23 * m34 * _m41 - m24 * m31 * _m43);
	float r1y = d1 * (m11 * m33 * _m44 + m13 * m34 * _m41 + m14 * m31 * _m43 - m11 * m34 * _m43 - m13 * m31 * _m44 - m14 * m33 * _m41);
	float r1z = d1 * (m11 * m24 * _m43 + m13 * m21 * _m44 + m14 * m23 * _m41 - m11 * m23 * _m44 - m13 * m24 * _m41 - m14 * m21 * _m43);
	float r1w = d1 * (m11 * m23 * m34 + m13 * m24 * m31 + m14 * m21 * m33 - m11 * m24 * m33 - m13 * m21 * m34 - m14 * m23 * m31);
	result->Row1(new Vector4f(r1x, r1y, r1z, r1w));

	float r2x = d1 * (m21 * m32 * _m44 + m22 * m34 * _m41 + m24 * m31 * _m42 - m21 * m34 * _m42 - m22 * m31 * _m44 - m24 * m32 * _m41);
	float r2y = d1 * (m11 * m34 * _m42 + m12 * m31 * _m44 + m14 * m32 * _m41 - m11 * m32 * _m44 - m12 * m34 * _m41 - m14 * m31 * _m42);
	float r2z = d1 * (m11 * m22 * _m44 + m12 * m24 * _m41 + m14 * m21 * _m42 - m11 * m24 * _m42 - m12 * m21 * _m44 - m14 * m22 * _m41);
	float r2w = d1 * (m11 * m24 * m32 + m12 * m21 * m34 + m14 * m22 * m31 - m11 * m22 * m34 - m12 * m24 * m31 - m14 * m21 * m32);
	result->Row2(new Vector4f(r2x, r2y, r2z, r2w));

	float r3x = d1 * (m21 * m33 * _m42 + m22 * m31 * _m43 + m23 * m32 * _m41 - m21 * m32 * _m43 - m22 * m33 * _m41 - m23 * m31 * _m42);
	float r3y = d1 * (m11 * m32 * _m43 + m12 * m33 * _m41 + m13 * m31 * _m42 - m11 * m33 * _m42 - m12 * m31 * _m43 - m13 * m32 * _m41);
	float r3z = d1 * (m11 * m23 * _m42 + m12 * m21 * _m43 + m13 * m22 * _m41 - m11 * m22 * _m43 - m12 * m23 * _m41 - m13 * m21 * _m42);
	float r3w = d1 * (m11 * m22 * m33 + m12 * m23 * m31 + m13 * m21 * m32 - m11 * m23 * m32 - m12 * m21 * m33 - m13 * m22 * m31);
	result->Row3(new Vector4f(r3x, r3y, r3z, r3w));

	(*out_result) = result;
}

Matrix4* Matrix4::InvertAffine()
{
	Matrix4* result = Matrix4::Identity();
	float _m11 = this->Row0()->x;
	float _m12 = Row0()->y;
	float _m13 = Row0()->z;
	float _m14 = Row0()->w;
	float _m21 = Row1()->x;
	float _m22 = Row1()->y;
	float _m23 = Row1()->z;
	float _m24 = Row1()->w;
	float _m31 = Row2()->x;
	float _m32 = Row2()->y;
	float _m33 = Row2()->z;
	float _m34 = Row2()->w;

	float d = _m11 * _m22 * _m33 + _m21 * _m32 * _m13 + _m31 * _m12 * _m23 -
		_m11 * _m32 * _m23 - _m31 * _m22 * _m13 - _m21 * _m12 * _m33;

	if (d == 0.0f) {
		//std::cout << "Matrix is singular and cannot be inverted." << std::endl;
		return this;
	}
	float d1 = 1 / d;

	result->Row0(
		new Vector4f(d1 * (_m22 * _m33 - _m23 * _m32),
			d1 * (_m13 * _m32 - _m12 * _m33),
			d1 * (_m12 * _m23 - _m13 * _m22),
			0.0f)
	);
	result->Row1(
		new Vector4f(d1 * (_m23 * _m31 - _m21 * _m33),
			d1 * (_m11 * _m33 - _m13 * _m31),
			d1 * (_m13 * _m21 - _m11 * _m23),
			0.0f)
	);
	result->Row2(
		new Vector4f(d1 * (_m21 * _m32 - _m22 * _m31),
			d1 * (_m12 * _m31 - _m11 * _m32),
			d1 * (_m11 * _m22 - _m12 * _m21),
			0.0f)
	);

	result->Row0(new Vector4f(
		result->Row0()->x, // sub 3x3 inv 
		result->Row0()->y,
		result->Row0()->z,
		-result->Row0()->x * _m14 - result->Row0()->y * _m24 - result->Row0()->z * _m34 // - sub 3x3 inv * b
	));

	result->Row1(new Vector4f(
		result->Row1()->x, // sub 3x3 inv
		result->Row1()->y,
		result->Row1()->z,
		-result->Row1()->x * _m14 - result->Row1()->y * _m24 - result->Row1()->z * _m34 // - sub 3x3 inv * b
	));

	result->Row2(new Vector4f(
		result->Row2()->x, // sub 3x3 inv
		result->Row2()->y,
		result->Row2()->z,
		-result->Row2()->x * _m14 - result->Row2()->y * _m24 - result->Row2()->z * _m34 // - sub 3x3 inv * b
	));

	// last row remains 0 0 0 1
	result->Row3(new Vector4f(
		0.0f,
		0.0f,
		0.0f,
		1.0f
	));
}

Matrix4::Matrix4() { }

Matrix4::Matrix4(Vector4f* row0, Vector4f* row1, Vector4f* row2, Vector4f* row3)
{
	m00 = row0->x;
	m01 = row0->y;
	m02 = row0->z;
	m03 = row0->w;

	m10 = row1->x;
	m11 = row1->y;
	m12 = row1->z;
	m13 = row1->w;

	m20 = row2->x;
	m21 = row2->y;
	m22 = row2->z;
	m23 = row2->w;

	m30 = row3->x;
	m31 = row3->y;
	m32 = row3->z;
	m33 = row3->w;
}

//Matrix4 Matrix4::CreateClipMatrix(float width, float height, float nearDepth, float farDepth)
//{
//    float n = (w1 - nearDepth) / (w1 - w2);

//    return new Matrix4(
//        new Vector4(2.0f * nearDepth * invRL, 0.0f, 0.0f, 0.0f),
//        new Vector4(0.0f, 2.0f * nearDepth * invTB, 0.0f, 0.0f),
//        new Vector4((right + left) * invRL, (top + bottom) * invTB, -(farDepth + nearDepth) * invFN, -1.0f),
//        new Vector4(0.0f, 0.0f, -2.0f * farDepth * nearDepth * invFN, 0.0f)
//    );
//}

Matrix4* Matrix4::CreateSQTMatrix(Vector3f* scale, Quaternion* rotation, Vector3f* translation)
{
	// Manual SRT 4x4 Matrix

	Matrix4* matrixSRT = Matrix4::Identity();

	matrixSRT->Scale(scale);
	matrixSRT = Matrix4::Multiply(matrixSRT, CreateRotatationMatrix(rotation));
	matrixSRT->Translate(translation);

	return matrixSRT;
}

void Matrix4::SetTRS(Vector3f* translation, Quaternion* rotation, Vector3f* scale)
{
	Matrix4* result = this;
	Matrix4* scaleMatrix = Matrix4::CreateScaleMatrix(scale);
	Matrix4* rotationMatrix = CreateRotatationMatrix(rotation);
	Matrix4* translationMatrix = CreateTranslationMatrix(translation);

	result = Multiply(result, scaleMatrix);
	result = Multiply(result, rotationMatrix);
	result = Multiply(result, translationMatrix);

	this->Row0(result->Row0());
	this->Row1(result->Row1());
	this->Row2(result->Row2());
	this->Row3(result->Row3());
}

void Matrix4::Scale(float uniform_scalar) 
{
	Vector4f* r0 = Row0();
	Vector4f* r1 = Row0();
	Vector4f* r2 = Row0();
	Vector4f* r3 = Row0();

	Vector4f* i0 = new Vector4f(uniform_scalar, 1, 1, 1);
	Vector4f* i1 = new Vector4f(1, uniform_scalar, 1, 1);
	Vector4f* i2 = new Vector4f(1, 1, uniform_scalar, 1);

	r0 = r0->Multiply(r0, i0);
	r1 = r1->Multiply(r1, i1);
	r2 = r2->Multiply(r2, i2);
	r3->w = 1.0f;

	Row0(r0);
	Row1(r1);
	Row2(r2);
	Row3(r3);
}
void Matrix4::Scale(Vector3f* scale)
{
	Vector4f* r0 = Row0();
	Vector4f* r1 = Row0();
	Vector4f* r2 = Row0();
	Vector4f* r3 = Row0();

	Vector4f* i0 = new Vector4f(scale->x, 1, 1, 1);
	Vector4f* i1 = new Vector4f(1, scale->y, 1, 1);
	Vector4f* i2 = new Vector4f(1, 1, scale->z, 1);

	r0 = r0->Multiply(r0, i0);
	r1 = r1->Multiply(r1, i1);
	r2 = r2->Multiply(r2, i2);
	r3->w = 1.0f;

	Row0(r0);
	Row1(r1);
	Row2(r2);
	Row3(r3);
}

void Matrix4::Scale(Vector4f* scale)
{
	Vector4f* r0 = Row0();
	Vector4f* r1 = Row0();
	Vector4f* r2 = Row0();
	Vector4f* r3 = Row0();

	Vector4f* i0 = new Vector4f(scale->x, 1, 1, 1);
	Vector4f* i1 = new Vector4f(1, scale->y, 1, 1);
	Vector4f* i2 = new Vector4f(1, 1, scale->z, 1);
	Vector4f* i3 = new Vector4f(1, 1, 1, scale->w);

	r0 = r0->Multiply(r0, i0);
	r1 = r1->Multiply(r1, i1);
	r2 = r2->Multiply(r2, i2);
	r3 = r3->Multiply(r3, i3);

	Row0(r0);
	Row1(r1);
	Row2(r2);
	Row3(r3);
}

Vector3f* Matrix4::GetScale()
{
	return new Vector3f(Row0()->x, Row1()->y, Row2()->z);
}

void Matrix4::RotateX(float angleInDegrees)
{
	float angleInRadians = Deg2Rad * angleInDegrees;
	Matrix4* rotationMatrix = new Matrix4();
	rotationMatrix->Row0(Vector4f::UnitX);
	rotationMatrix->Row1(new Vector4f(0, cos(angleInRadians), -sin(angleInRadians), 0.0f));
	rotationMatrix->Row1(new Vector4f(0, sin(angleInRadians), cos(angleInRadians), 0.0f));

	Matrix4* result;
	result = Multiply(this, rotationMatrix);
	this->Row0(result->Row0());
	this->Row1(result->Row1());
	this->Row2(result->Row2());
	this->Row3(result->Row3());
}

void Matrix4::RotateY(float angleInDegrees)
{
	float angleInRadians = Deg2Rad * angleInDegrees;
	Matrix4* rotationMatrix = new Matrix4();
	rotationMatrix->Row0(new Vector4f(cos(angleInRadians), 0, sin(angleInRadians), 0.0f));
	rotationMatrix->Row1(Vector4f::UnitY);
	rotationMatrix->Row2(new Vector4f(-sin(angleInRadians), 0, cos(angleInRadians), 0.0f));

	Matrix4* result;
	result = Multiply(this, rotationMatrix);
	this->Row0(result->Row0());
	this->Row1(result->Row1());
	this->Row2(result->Row2());
	this->Row3(result->Row3());
}

void Matrix4::RotateZ(float angleInDegrees)
{
	float angleInRadians = Deg2Rad * angleInDegrees;
	Matrix4* rotationMatrix = new Matrix4();
	rotationMatrix->Row0(new Vector4f(cos(angleInRadians), -sin(angleInRadians), 0.0f, 0.0f));
	rotationMatrix->Row1(new Vector4f(sin(angleInRadians), cos(angleInRadians), 0.0f, 0.0f));
	rotationMatrix->Row2(Vector4f::UnitZ);

	Matrix4* result;
	result = Multiply(this, rotationMatrix);
	this->Row0(result->Row0());
	this->Row1(result->Row1());
	this->Row2(result->Row2());
	this->Row3(result->Row3());
}

void Matrix4::Rotate(Vector2f* angleXY)
{
	Matrix4* result;
	Matrix4* rotationMatrixX = CreateRotationXMatrix(angleXY->x);
	Matrix4* rotationMatrixY = CreateRotationYMatrix(angleXY->y);
	result = Multiply(this, rotationMatrixX);
	result = Multiply(result, rotationMatrixY);
	this->Row0(result->Row0());
	this->Row1(result->Row1());
	this->Row2(result->Row2());
	this->Row3(result->Row3());
}

Matrix4* Matrix4::RotationYawPitchRoll(float rotationYYawInDegrees, float rotationXPitchInDegrees, float rotationZRollInDegrees)
{
	Matrix4* rotationMatrix = Matrix4::Identity();
	rotationMatrix->RotateX(rotationXPitchInDegrees);
	rotationMatrix->RotateY(rotationYYawInDegrees);
	rotationMatrix->RotateZ(rotationZRollInDegrees);
	return rotationMatrix;
}

void Matrix4::SetTranslation(Vector3f* translation)
{
	Vector4f* row3 = Row3();
	Vector4f* translate = new Vector4f(translation, 0.0f);
	Row3(translate);
}

void Matrix4::Translate(Vector3f* translation)
{
	Vector4f* row3 = Row3();
	Vector4f* translate = new Vector4f(translation, 0.0f);
	row3 = row3->Add(row3, translate);
	row3->w = 1.0f;
	Row3(row3);
}

Vector3f* Matrix4::GetTranslation()
{
	return Row3()->xyz();
}

Vector4f* Matrix4::GetTranslation4()
{
	return Row3();
}

void Matrix4::Translate(Vector4f* translation)
{
	Vector4f* row3 = Row3();
	row3 = row3->Add(row3, translation);
	Row3(row3);
}

Matrix4* Matrix4::Transpose()
{
	Matrix4* t = new Matrix4();
	t->Row0(Column0());
	t->Row1(Column1());
	t->Row2(Column2());
	t->Row3(Column3());
	return t;
}

float* Matrix4::ToArray()
{
	return new float[16]
		{
			m00, m01, m02, m03,
				m10, m11, m12, m13,
				m20, m21, m22, m23,
				m30, m31, m32, m33
		};
}

float& Matrix4::operator[](const int index)
{
	if (index >= size) {
		//std::cout << "Array index out of bound, exiting";
		//exit(-1);
		float empty = 0.0f;
		return empty;
	}
	return ToArray()[index];
}

//float& operator[](const int row, const int column) // Cant do in c++.
//{
//    if (index >= size) {
//        //std::cout << "Array index out of bound, exiting";
//        //exit(-1);
//        return;
//    }
//    return ToArray()[row * 4 + column];
//}

//// Multiply.
//Matrix4* Matrix4::operator*(Matrix4* right) const {
//	return Matrix4::Multiply((Matrix4*)this, right);
//}
//Matrix4* Matrix4::operator*(Vector4f* right) const {
//	return Matrix4::Multiply((Matrix4*)this, right);
//}
//Matrix4* Matrix4::operator*(Vector3f* right) const {
//	return Matrix4::Multiply((Matrix4*)this, right->xyzw());
//}
//Matrix4* Matrix4::operator*(Vector2f* right) const {
//	return Matrix4::Multiply((Matrix4*)this, right->xyzw());
//}

Matrix4* Matrix4::AnglesToRotationMatrix(Vector3f* angles)
{
	float sx, sy, sz, cx, cy, cz, theta;
	Vector3f* left;
	Vector3f* up;
	Vector3f* forward;

	// rotation angle about X-axis (pitch)
	theta = angles->x * Deg2Rad;
	sx = sinf(theta);
	cx = cosf(theta);

	// rotation angle about Y-axis (yaw)
	theta = -angles->y * Deg2Rad;
	sy = sinf(theta);
	cy = cosf(theta);

	// rotation angle about Z-axis (roll)
	theta = angles->z * Deg2Rad;
	sz = sinf(theta);
	cz = cosf(theta);

	// determine left axis
	left = new Vector3f(
		cy * cz,
		sx * sy * cz + cx * sz,
		-cx * sy * cz + sx * sz
	);

	// determine up axis
	up = new Vector3f(
		-cy * sz,
		-sx * sy * sz + cx * cz,
		cx * sy * sz + sx * cz
	);

	// determine forward axis
	forward = new Vector3f(
		sy,
		-sx * cy,
		cx * cy
	);

	// construct rotation matrix
	Matrix4* matrix = Identity();
	matrix->Column0(left->xyzw());
	matrix->Column1(up->xyzw());
	matrix->Column2(forward->xyzw());

	return matrix;
}

Matrix4* Matrix4::CreateFromAxisAngle(Vector3f* axis, float angle)
{
	// normalize and create a local copy of the vector.
	axis = axis->Normalise();
	float axisX = axis->x;
	float axisY = axis->y;
	float axisZ = axis->z;

	// calculate angles
	float cosine = (float)cos(-angle);
	float sine = (float)sin(-angle);
	float t = 1.0f - cosine;

	// do the conversion math once
	float tXX = t * axisX * axisX,
		tXY = t * axisX * axisY,
		tXZ = t * axisX * axisZ,
		tYY = t * axisY * axisY,
		tYZ = t * axisY * axisZ,
		tZZ = t * axisZ * axisZ;

	float sinX = sine * axisX,
		sinY = sine * axisY,
		sinZ = sine * axisZ;

	Matrix4* result = Identity();
	result->Row0(new Vector4f(
		tXX + cosine,
		tXY - sinZ,
		tXZ + sinY,
		0.0f
	));
	result->Row1(new Vector4f(
		tXY + sinZ,
		tYY + cosine,
		tYZ - sinX,
		0.0f
	));
	result->Row2(new Vector4f(
		tXZ - sinY,
		tYZ + sinX,
		tZZ + cosine,
		0.0f
	));
	result->Row3(new Vector4f(0.0f, 0.0f, 0.0f, 1.0f));
	return result;
}

Matrix4* Matrix4::Multiply(Matrix4* left, Matrix4* right)
{
	Matrix4* result = new Matrix4();

	// Column 0
	result->m00 = Vector4f::Dot(left->Row0(), right->Column0());
	result->m01 = Vector4f::Dot(left->Row0(), right->Column1());
	result->m02 = Vector4f::Dot(left->Row0(), right->Column2());
	result->m03 = Vector4f::Dot(left->Row0(), right->Column3());

	// Column 1
	result->m10 = Vector4f::Dot(left->Row1(), right->Column0());
	result->m11 = Vector4f::Dot(left->Row1(), right->Column1());
	result->m12 = Vector4f::Dot(left->Row1(), right->Column2());
	result->m13 = Vector4f::Dot(left->Row1(), right->Column3());

	// Column 2
	result->m20 = Vector4f::Dot(left->Row2(), right->Column0());
	result->m21 = Vector4f::Dot(left->Row2(), right->Column1());
	result->m22 = Vector4f::Dot(left->Row2(), right->Column2());
	result->m23 = Vector4f::Dot(left->Row2(), right->Column3());

	// Column 3
	result->m30 = Vector4f::Dot(left->Row3(), right->Column0());
	result->m31 = Vector4f::Dot(left->Row3(), right->Column1());
	result->m32 = Vector4f::Dot(left->Row3(), right->Column2());
	result->m33 = Vector4f::Dot(left->Row3(), right->Column3());

	return result;
}

Matrix4* Matrix4::Multiply(Matrix4* left, Vector4f* right)
{
	Matrix4* result = new Matrix4();

	result->m00 = (left->m00 * right->x);
	result->m01 = (left->m00 * right->y);
	result->m02 = (left->m00 * right->z);
	result->m03 = (left->m00 * right->w);

	result->m10 = (left->m10 * right->x);
	result->m11 = (left->m10 * right->y);
	result->m12 = (left->m10 * right->z);
	result->m13 = (left->m10 * right->w);

	result->m20 = (left->m20 * right->x);
	result->m21 = (left->m20 * right->y);
	result->m22 = (left->m20 * right->z);
	result->m23 = (left->m20 * right->w);

	result->m30 = (left->m30 * right->x);
	result->m31 = (left->m30 * right->y);
	result->m32 = (left->m30 * right->z);
	result->m33 = (left->m30 * right->w);

	return result;
}

Vector2f* Matrix4::TransformVector(Matrix4* left, Vector2f* right)
{
	Vector2f* result = new Vector2f(); // Neater to do with Dot Products.
	result->x = Vector2f::Dot(right, left->Column0()->xy());
	result->y = Vector2f::Dot(right, left->Column1()->xy());
	return result;
}

Vector3f* Matrix4::TransformVector(Matrix4* left, Vector3f* right)
{
	Vector3f* result = new Vector3f(); // Neater to do with Dot Products.
	result->x = Vector3f::Dot(left->Column0()->xyz(), right);
	result->y = Vector3f::Dot(left->Column1()->xyz(), right);
	result->z = Vector3f::Dot(left->Column2()->xyz(), right);
	return result;
}

Vector4f* Matrix4::TransformVector(Matrix4* left, Vector4f* right)
{
	Vector4f* result = new Vector4f(); // Neater to do with Dot Products.
	result->x = Vector4f::Dot(right, left->Column0());
	result->y = Vector4f::Dot(right, left->Column1());
	result->z = Vector4f::Dot(right, left->Column2());
	result->w = Vector4f::Dot(right, left->Column3());
	return result;
}

Vector3f* Matrix4::TransformVector(Vector3f* vector)
{
	Vector3f* result = new Vector3f();
	Vector4f* left = new Vector4f(vector, 1.0f);
	result->x = Vector4f::Dot(left, this->Column0());
	result->y = Vector4f::Dot(left, this->Column1());
	result->z = Vector4f::Dot(left, this->Column2());
	// Neater to do with Dot Products.
	return result;
}

Vector3f* Matrix4::TransformPosition(Vector3f* vector)
{
	Vector3f* translation = GetTranslation();
	Vector3f* result = new Vector3f(
		Vector3f::Dot(vector, this->Column0()->xyz()) + translation->x,
		Vector3f::Dot(vector, this->Column1()->xyz()) + translation->y,
		Vector3f::Dot(vector, this->Column2()->xyz()) + translation->z
	); // Neater to do with Dot Products.		
	return result;
}

Vector3f* Matrix4::TransformNormal(Vector3f* normal)
{
	Vector3f* result;
	Matrix4* transform = this;
	Matrix4* m = transform->Inverse();

	Vector3f* r0 = m->Row0()->xyz();
	Vector3f* r1 = m->Row1()->xyz();
	Vector3f* r2 = m->Row2()->xyz();

	Vector3f* tmp = new Vector3f
	(
		Vector3f::Dot(normal, r0),
		Vector3f::Dot(normal, r1),
		Vector3f::Dot(normal, r2)
	);

	result = tmp;

	return result;
}

Vector3f* Matrix4::TransformNormal(Matrix4* transform, Vector3f* normal)
{
	Vector3f* result;
	Matrix4* m = static_cast<Matrix4*>(transform)->Inverse();

	Vector3f* r0 = m->Row0()->xyz();
	Vector3f* r1 = m->Row1()->xyz();
	Vector3f* r2 = m->Row2()->xyz();

	Vector3f* tmp = new Vector3f
	(
		Vector3f::Dot(normal, r0),
		Vector3f::Dot(normal, r1),
		Vector3f::Dot(normal, r2)
	);

	result = tmp;

	return result;
}

Vector4f* Matrix4::TransformSRT(Vector4f* vector, Vector3f* scale, Vector3f* rotationAxis, Vector2f* xyRotationDeg, Vector3f* translation)
{
	// Manual SRT 4x4 Matrix

	Vector4f* result;
	Matrix4* matrixSRT;
	Vector2f* unitCircleRatioX;
	Vector2f* unitCircleRatioY;
	Vector2f* t;

	rotationAxis->Normalise();

	// Creates a rotation about rotationAxis given two angles specified in xyRotationDeg.
	unitCircleRatioX = new Vector2f(
		cos(-xyRotationDeg->x),
		sin(-xyRotationDeg->x)
	);
	unitCircleRatioY = new Vector2f(
		cos(-xyRotationDeg->y),
		sin(-xyRotationDeg->y)
	);

	t = new Vector2f(1.0f - unitCircleRatioX->x, 1.0f - unitCircleRatioY->x);

	Vector4f* row0Rotation = new Vector4f(
		((t->y * rotationAxis->x * rotationAxis->x) + unitCircleRatioY->x) * ((t->x * rotationAxis->x * rotationAxis->x) + unitCircleRatioX->x),
		((t->y * rotationAxis->x * rotationAxis->y - unitCircleRatioY->y * rotationAxis->z)) * ((t->x * rotationAxis->x * rotationAxis->y - unitCircleRatioX->y * rotationAxis->z)),
		((t->y * rotationAxis->x * rotationAxis->z + unitCircleRatioY->y * rotationAxis->y)) * ((t->x * rotationAxis->x * rotationAxis->z + unitCircleRatioX->y * rotationAxis->y)),
		0.0f
	);
	Vector4f* row1Rotation = new Vector4f(
		((t->y * rotationAxis->x * rotationAxis->y + unitCircleRatioY->y * rotationAxis->z)) * ((t->x * rotationAxis->x * rotationAxis->y + unitCircleRatioX->y * rotationAxis->z)),
		((t->y * rotationAxis->y * rotationAxis->y + unitCircleRatioY->x)) * ((t->x * rotationAxis->y * rotationAxis->y + unitCircleRatioX->x)),
		((t->y * rotationAxis->y * rotationAxis->z - unitCircleRatioY->y * rotationAxis->x)) * ((t->x * rotationAxis->y * rotationAxis->z - unitCircleRatioX->y * rotationAxis->x)),
		0.0f
	);
	Vector4f* row2Rotation = new Vector4f(
		((t->y * rotationAxis->x * rotationAxis->z - unitCircleRatioY->y * rotationAxis->y)) * ((t->x * rotationAxis->x * rotationAxis->z - unitCircleRatioX->y * rotationAxis->y)),
		((t->y * rotationAxis->y * rotationAxis->z + unitCircleRatioY->y * rotationAxis->x)) * ((t->x * rotationAxis->y * rotationAxis->z + unitCircleRatioX->y * rotationAxis->x)),
		((t->y * rotationAxis->z * rotationAxis->z + unitCircleRatioY->x)) * ((t->x * rotationAxis->z * rotationAxis->z + unitCircleRatioX->x)),
		0.0f
	);

	// Create the SRT Matrix.
	Vector4f* scalar0 = new Vector4f(scale->x, 0, 0, 0);
	Vector4f* scalar1 = new Vector4f(0, scale->y, 0, 0);
	Vector4f* scalar2 = new Vector4f(0, 0, scale->z, 0);

	matrixSRT = Matrix4::Identity();
	matrixSRT->Row0(matrixSRT->Row0()->Scale(matrixSRT->Row0(), scalar0));
	matrixSRT->Row1(matrixSRT->Row1()->Scale(matrixSRT->Row1(), scalar1));
	matrixSRT->Row2(matrixSRT->Row2()->Scale(matrixSRT->Row2(), scalar2));
	matrixSRT->Row0(matrixSRT->Row0()->Scale(matrixSRT->Row0(), row0Rotation));
	matrixSRT->Row1(matrixSRT->Row1()->Scale(matrixSRT->Row1(), row1Rotation));
	matrixSRT->Row2(matrixSRT->Row2()->Scale(matrixSRT->Row2(), row2Rotation));
	matrixSRT->Row3(matrixSRT->Row3()->Add(matrixSRT->Row3(), new Vector4f(translation, 1.0f)));

	//result = matrixSRT * vector;
	result = TransformVector(matrixSRT, vector);

	return result;
}

Matrix4* Matrix4::CreateScaleMatrix(Vector3f* scale)
{
	Matrix4* scaleMatrix = new Matrix4();
	scaleMatrix->Row0(new Vector4f(scale->x, 0, 0, 0));
	scaleMatrix->Row1(new Vector4f(0, scale->y, 0, 0));
	scaleMatrix->Row2(new Vector4f(0, 0, scale->z, 0));
	scaleMatrix->Row3(Vector4f::UnitW);
	return scaleMatrix;
}

Matrix4* Matrix4::CreateRotationXMatrix(float angle)
{
	return CreateRotatationMatrix(Vector3f::UnitX, angle);
}

Matrix4* Matrix4::CreateRotationYMatrix(float angle)
{
	return CreateRotatationMatrix(Vector3f::UnitY, angle);
}

Matrix4* Matrix4::CreateRotationZMatrix(float angle)
{
	return CreateRotatationMatrix(Vector3f::UnitZ, angle);
}

Matrix4* Matrix4::CreateRotatationMatrix(Quaternion* q)
{
	Vector3f* axis = new Vector3f();
	float* angle = new float(0.0f);
	q->DeconstructQuaternion(&axis, &angle);
	return CreateRotatationMatrix(axis, *angle);
}

Matrix4* Matrix4::CreateRotatationMatrix(Vector3f* axis, float angle)
{
	float cosine = cos(-angle);
	float sine = sin(-angle);
	float t = 1.0f - cosine;

	axis = axis->Normalise();

	Matrix4* result = new Matrix4();
	result->Row0(new Vector4f(
		(t * axis->x * axis->x) + cosine,
		(t * axis->x * axis->y - sine * axis->z),
		(t * axis->x * axis->z + sine * axis->y),
		0.0f
	));
	result->Row1(new Vector4f(
		(t * axis->x * axis->y + sine * axis->z),
		(t * axis->y * axis->y + cosine),
		(t * axis->y * axis->z - sine * axis->x),
		0.0f
	));
	result->Row2(new Vector4f(
		(t * axis->x * axis->z - sine * axis->y),
		(t * axis->y * axis->z + sine * axis->x),
		(t * axis->z * axis->z + cosine),
		0.0f
	));
	result->Row3(new Vector4f(0.0f, 0.0f, 0.0f, 1.0f));
	return result;
}

Matrix4* Matrix4::CreateTranslationMatrix(Vector3f* translation) // refactor
{
	Matrix4* translationMatrix = Identity();
	translationMatrix->Row3(new Vector4f(translation, 1.0f));
	return translationMatrix;
}

Matrix4* Matrix4::Orthographic(float left, float right, float bottom, float top, float nearDistance, float farDistance)
{
	Matrix4* orthoMatrix = new Matrix4();

	float invertRL = 1 / (right - left);
	float invertTB = 1 / (top - bottom);
	float invertFN = 1 / (farDistance - nearDistance);

	orthoMatrix->Row0(Vector4f::Scale(Vector4f::UnitX, 2.0f * invertRL));
	orthoMatrix->Row1(Vector4f::Scale(Vector4f::UnitY, 2.0f * invertTB));
	orthoMatrix->Row2(Vector4f::Scale(Vector4f::UnitZ, -2.0f * invertFN));
	orthoMatrix->Row3(new Vector4f(
		-(right + left) * invertRL,
		-(top + bottom) * invertTB,
		-(farDistance + nearDistance) * invertFN,
		1.0f
	));

	return orthoMatrix;
}

Matrix4* Matrix4::Perspective(float fieldOfView, float aspectRatio, float nearDistance, float farDistance)
{
	Matrix4* perspectiveMatrix;

	float halfFov = (fieldOfView * 0.5f) * Deg2Rad;
	float top = nearDistance * tan(halfFov);
	float bottom = -top;
	float left = bottom * aspectRatio;
	float right = top * aspectRatio;

	//float xScale = (2.0f * nearDistance) / (right - left);
	//float yScale = (2.0f * nearDistance) / (top - bottom);
	//float a = (right + left) / (right - left);
	//float b = (top + bottom) / (top - bottom);
	//float zScale = -(farDistance + nearDistance) / (farDistance - nearDistance);
	//float d = -(2.0f * farDistance * nearDistance) / (farDistance - nearDistance);

	//perspectiveMatrix = new Matrix4(
	//	Vector4f::Scale(new Vector4f(1.0f, 0.0f, 0.0f, 0.0f), xScale),
	//	Vector4f::Scale(new Vector4f(0.0f, 1.0f, 0.0f, 0.0f), yScale),
	//	new Vector4f(a, b, zScale, -1),
	//	Vector4f::Scale(new Vector4f(0.0f, 0.0f, 1.0f, 0.0f), d)
	//);

	float x = (2.0f * nearDistance) / (right - left);
	float y = (2.0f * nearDistance) / (top - bottom);
	float a = (right + left) / (right - left);
	float b = (top + bottom) / (top - bottom);
	float c = -(farDistance + nearDistance) / (farDistance - nearDistance);
	float d = -(2.0f * farDistance * nearDistance) / (farDistance - nearDistance);

	perspectiveMatrix = new Matrix4(
		new Vector4f(x, 0.0f, 0.0f, 0.0f),
		new Vector4f(0.0f, y, 0.0f, 0.0f),
		new Vector4f(a, b, c, -1.0f),
		new Vector4f(0.0f, 0.0f, d, 0.0f)
	);

	//perspectiveMatrix = Matrix4::Identity();
	return perspectiveMatrix;
}

Matrix4* Matrix4::CreateScreenSpaceMatrix(Vector2i halfSize)
{
	return new Matrix4(
		new Vector4f(halfSize.x, 0, 0, halfSize.x),
		new Vector4f(0, -halfSize.y, 0, halfSize.y),
		Vector4f::UnitZ,
		Vector4f::UnitW
	);
}

Matrix4* Matrix4::CreateFrustumMatrix(float left, float right, float bottom, float top, float nearDepth, float farDepth)
{
	float invertRL = 1.0f / (right - left);
	float invertTB = 1.0f / (top - bottom);
	float invertFN = 1.0f / (farDepth - nearDepth);

	return new Matrix4(
		Vector4f::Scale(Vector4f::UnitX, 2.0f * nearDepth * invertRL),
		Vector4f::Scale(Vector4f::UnitY, 2.0f * nearDepth * invertTB),
		new Vector4f((right + left) * invertRL, (top + bottom) * invertTB, -(farDepth + nearDepth) * invertFN, -1.0f),
		Vector4f::Scale(Vector4f::UnitZ, -2.0f * farDepth * nearDepth * invertFN)
	);
}

Matrix4* Matrix4::LookAt(Vector3f* eye, Vector3f* target, Vector3f* up)
{
	Vector3f* z = (Vector3f::Subtract(eye, target))->Normalised();
	Vector3f* x = Vector3f::Cross(up, z)->Normalised();
	Vector3f* y = Vector3f::Cross(z, x)->Normalised();

	Matrix4* rot = new Matrix4(
		new Vector4f(x->x, y->x, z->x, 0.0f),
		new Vector4f(x->y, y->y, z->y, 0.0f),
		new Vector4f(x->z, y->z, z->z, 0.0f),
		new Vector4f(0.0f, 0.0f, 0.0f, 1.0f)
	);

	Matrix4* trans = CreateTranslationMatrix(new Vector3f(-eye->x, -eye->y, -eye->z));

	return Matrix4::Multiply(trans, rot);
}