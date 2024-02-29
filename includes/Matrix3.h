#ifndef MATRIX3_H
#define MATRIX3_H

#include "Vector2i.h"
#include "Vector2f.h"
#include "Vector3f.h"
#include "Vector4f.h"
#include "Quaternion.h"

class Matrix3;
class Vector4f;
class Vector3f;
class Vector2f;
class Vector2i;

class Matrix3
{
public:
	//static Matrix3 Identity;

	// Matrix Values

	// Row 0
	float m00;
	float m01;
	float m02;

	// Row 1
	float m10;
	float m11;
	float m12;

	// Row 2
	float m20;
	float m21;
	float m22;

	// Row 3
	float m30;
	float m31;
	float m32;

	// Constructors
	Matrix3();

	Matrix3(
		Vector3f* row0,
		Vector3f* row1,
		Vector3f* row2
	);

    Matrix3(float m00, float m01, float m02,
            float m10, float m11, float m12,
            float m20, float m21, float m22);

	// Matrix Rows
	Vector3f* GetRow0() const;
	Vector3f* GetRow1() const;
	Vector3f* GetRow2() const;
	void SetRow0(Vector3f* row0);
	void SetRow1(Vector3f* row1);
	void SetRow2(Vector3f* row2);
	// Matrix Rows

	// Matrix Columns

	Vector3f* GetColumn0() const;
	Vector3f* GetColumn1() const;
	Vector3f* GetColumn2() const;

	void SetColumn0(Vector3f* column0);
	void SetColumn1(Vector3f* column1);
	void SetColumn2(Vector3f* column2);

	// Matrix Columns

	static Matrix3* GetIdentity();

	Matrix3* Transpose();

	float GetMagnitude() const;
	float GetDeterminant() const;

	Matrix3* Inverse();
	Matrix3* Invert(Matrix3* m);
	Vector3f* GetDiagonal();

	float* ToArray();

	void FromArray(float* arr);

	// correct multipliers.
	void Multiply(Matrix3* right);

	static Matrix3* Multiply(Matrix3* left, Matrix3* right);

	static Matrix3* Multiply(Matrix3* left, Vector3f* right);

	static Vector2f* TransformVector(Matrix3* left, Vector2f* right);

	static Vector3f* TransformVector(Matrix3* left, Vector3f* right);

	Vector3f* TransformVector(Vector3f* vector);

	Vector3f* TransformNormal(Vector3f* normal);

	static Vector3f* TransformNormal(Matrix3* transform, Vector3f* normal);

	/// Get value in the matrix given the specified index.
	float operator [] (int index) const
	{
		return (&m00)[index];
	}
	/// Get value in the matrix given the specified index.
	float GetValue(int index) const;

	/// Set a value in the matrix given the specified index.
	void SetValue(int index, float value);



	//Matrix3 operator *(Matrix3 right) {
	//	Matrix3 result = static_cast<Matrix3>(Multiply(*this, right));
	//	return result;
	//}
	//Vector4 operator *(Vector4 right) {
	//	Vector4 result = static_cast<Vector4>(TransformVector(*this, right));
	//	return result;
	//}
	//Vector3 operator *(Vector3 right) {
	//	Vector3 result = static_cast<Vector3>(TransformVector(*this, right));
	//	return result;
	//}
	//Vector2 operator *(Vector2 right) {
	//	Vector2 result = static_cast<Vector2>(TransformVector(*this, right));
	//	return result;
	//}
};


//inline Matrix3* operator *=(Matrix3* left, Matrix3* right) {
//	Matrix3* lhs = static_cast<Matrix3*>(left);
//	return Matrix3::Multiply(lhs, right);
//}

//inline Matrix3* operator *(Matrix3* left, Matrix3* right) { return Matrix3::Multiply(left, right); }
////inline Vector4 operator *(Matrix3 left, Vector4 right) { return Matrix3::TransformVector(left, right); }
//inline Vector3* operator *(Matrix3* left, Vector3* right) { return Matrix3::TransformVector(left, right); }
////inline Vector2 operator *(Matrix3 left, Vector2 right) { return Matrix3::TransformVector(left, right); }

#endif