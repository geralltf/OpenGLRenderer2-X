#ifndef MATRIX4_H
#define MATRIX4_H

#include <cmath>

//class Vector2i;
//class Vector3f;
//class Vector2f;
//class Vector4f;
//class Matrix4;
//class Quaternion;

#include "VectorLib.h"
#include "Quaternion.h"
#include "MathLib.h"
#include "Vector2f.h"
#include "Vector3f.h"
#include "Vector4f.h"



class Matrix4
{
public:
    // Row 0
    float m00;
    float m01;
    float m02;
    float m03;

    // Row 1
    float m10;
    float m11;
    float m12;
    float m13;

    // Row 2
    float m20;
    float m21;
    float m22;
    float m23;

    // Row 3
    float m30;
    float m31;
    float m32;
    float m33;

    const size_t size = 16;

    Vector4f* Row0();
    Vector4f* Row1();
    Vector4f* Row2();
    Vector4f* Row3();
    void Row0(Vector4f* value);
    void Row1(Vector4f* value);
    void Row2(Vector4f* value);
    void Row3(Vector4f* value);

    void Column0(Vector4f* column0_values);

    void Column1(Vector4f* column1_values);
    void Column2(Vector4f* column2_values);

    void Column3(Vector4f* column3_value);

    Vector4f* Column0();

    Vector4f* Column1();

    Vector4f* Column2();

    Vector4f* Column3();


    static Matrix4* Identity();

    float Determinant();
    Matrix4* Inverse();
    void Invert(Matrix4** out_result);
    Matrix4* InvertAffine();

    Matrix4();

    Matrix4(Vector4f* row0, Vector4f* row1, Vector4f* row2, Vector4f* row3);

    //public static Matrix4 CreateClipMatrix(float width, float height, float nearDepth, float farDepth)
    //{
    //    float n = (w1 - nearDepth) / (w1 - w2);

    //    return new Matrix4(
    //        new Vector4(2.0f * nearDepth * invRL, 0.0f, 0.0f, 0.0f),
    //        new Vector4(0.0f, 2.0f * nearDepth * invTB, 0.0f, 0.0f),
    //        new Vector4((right + left) * invRL, (top + bottom) * invTB, -(farDepth + nearDepth) * invFN, -1.0f),
    //        new Vector4(0.0f, 0.0f, -2.0f * farDepth * nearDepth * invFN, 0.0f)
    //    );
    //}
    
    static Matrix4* CreateSQTMatrix(Vector3f* scale, Quaternion* rotation, Vector3f* translation);

    void SetTRS(Vector3f* translation, Quaternion* rotation, Vector3f* scale);


    static Matrix4* Scale(float x, float y, float z);

    void Scale(float scalar);

    void Scale(Vector3f* scale);

    void Scale(Vector4f* scale);

    Vector3f* GetScale();

    void RotateX(float angleInDegrees);

    void RotateY(float angleInDegrees);

    void RotateZ(float angleInDegrees);

    void Rotate(Vector2f* angleXY);

    static Matrix4* RotationYawPitchRoll(float rotationYYawInDegrees, float rotationXPitchInDegrees, float rotationZRollInDegrees);

    void SetTranslation(Vector3f* translation);
    void Translate(Vector3f* translation);

    Vector3f* GetTranslation();

    Vector4f* GetTranslation4();

    void Translate(Vector4f* translation);

    Matrix4* Transpose();

    float* ToArray();

    float& operator[](const int index);

    //float& operator[](const int row, const int column) // Cant do in c++.
    //{
    //    if (index >= size) {
    //        //std::cout << "Array index out of bound, exiting";
    //        //exit(-1);
    //        return;
    //    }
    //    return ToArray()[row * 4 + column];
    //}

    // Multiply.
    //Matrix4* operator*(Matrix4* right) const;
    //Matrix4* operator*(Vector4f* right) const;
    //Matrix4* operator*(Vector3f* right) const;
    //Matrix4* operator*(Vector2f* right) const;

    static Matrix4* AnglesToRotationMatrix(Vector3f* angles);
    static Matrix4* CreateFromAxisAngle(Vector3f* axis, float angle);

    static Matrix4* Multiply(Matrix4* left, Matrix4* right);

    static Matrix4* Multiply(Matrix4* left, Vector4f* right);

    static Vector2f* TransformVector(Matrix4* left, Vector2f* right);

    static Vector3f* TransformVector(Matrix4* left, Vector3f* right);

    static Vector4f* TransformVector(Matrix4* left, Vector4f* right);

    Vector3f* TransformVector(Vector3f* vector);
    Vector3f* TransformPosition(Vector3f* vector);
    Vector3f* TransformNormal(Vector3f* normal);
    Vector3f* TransformNormal(Matrix4* transform, Vector3f* normal);

    Vector4f* TransformSRT(Vector4f* vector, Vector3f* scale, Vector3f* rotationAxis, Vector2f* xyRotationDeg, Vector3f* translation);

    static Matrix4* CreateScaleMatrix(Vector3f* scale);

    static Matrix4* CreateRotationXMatrix(float angle);

    static Matrix4* CreateRotationYMatrix(float angle);

    static Matrix4* CreateRotationZMatrix(float angle);

    static Matrix4* CreateRotatationMatrix(Quaternion* q);

    static Matrix4* CreateRotatationMatrix(Vector3f* axis, float angle);

    static Matrix4* CreateTranslationMatrix(Vector3f* translation); // refactor


    static Matrix4* Orthographic(float left, float right, float bottom, float top, float nearDistance, float farDistance);

    static Matrix4* Perspective(float fieldOfView, float aspectRatio, float nearDistance, float farDistance);

    static Matrix4* CreateScreenSpaceMatrix(Vector2i halfSize);

    static Matrix4* CreateFrustumMatrix(float left, float right, float bottom, float top, float nearDepth, float farDepth);

    static Matrix4* LookAt(Vector3f* eye, Vector3f* target, Vector3f* up);
};

#endif