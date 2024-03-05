#include "Quaternion.h"

Vector2f* Quaternion::xy()
{
    Vector2f* result;
    result = new Vector2f(x, y);
    return result;
}
void Quaternion::xy(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vector3f* Quaternion::xyz()
{
    Vector3f* result;
    result = new Vector3f(x, y, z);
    return result;
}
void Quaternion::xyz(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector4f* Quaternion::xyzw()
{
    Vector4f* result;
    result = new Vector4f(x, y, z, w);
    return result;
}
void Quaternion::xyzw(float x, float y, float z, float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}
void Quaternion::xyzw(Vector4f* value)
{
    this->x = value->x;
    this->y = value->y;
    this->z = value->z;
    this->w = value->w;
}
Matrix4* Quaternion::RotationMatrix()
{
    return Matrix4::CreateRotatationMatrix(this);
}

Quaternion* Quaternion::Identity()
{
    return new Quaternion(0, 0, 0, 1);
}

Quaternion::Quaternion() { }

Quaternion::Quaternion(float x, float y, float z, float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Quaternion::Quaternion(Vector4f* vector)
{
    xyzw(vector);
}

Quaternion::Quaternion(Vector3f* vector, float w)
{
    xyzw(new Vector4f(vector, w));
}

Quaternion::Quaternion(Matrix4* matrix)
{
    float scale = pow(matrix->Determinant(), 1.0f / 3.0f);

    w = (sqrt(std::max(0.0f, scale + matrix->m00 + matrix->m11 + matrix->m22)) / 2.0f);
    x = (sqrt(std::max(0.0f, scale + matrix->m00 - matrix->m11 - matrix->m22)) / 2.0f);
    y = (sqrt(std::max(0.0f, scale - matrix->m00 + matrix->m11 - matrix->m22)) / 2.0f);
    z = (sqrt(std::max(0.0f, scale - matrix->m00 - matrix->m11 + matrix->m22)) / 2.0f);

    if (matrix->m12 - matrix->m12 < 0)
    {
        x = -x;
    }
    if (matrix->m02 - matrix->m20 < 0)
    {
        y = -y;
    }
    if (matrix->m10 - matrix->m01 < 0)
    {
        z = -z;
    }

    //if (matrix[2, 1] - matrix[1, 2] < 0) X = -X;
    //if (matrix[0, 2] - matrix[2, 0] < 0) Y = -Y;
    //if (matrix[1, 0] - matrix[0, 1] < 0) Z = -Z;
}

/// <summary>
/// Deconstruct quaternion into axis and angle
/// </summary>
/// <param name="axis"></param>
/// <param name="angle"></param>
void Quaternion::DeconstructQuaternion(Vector3f** axis, float** angle)
{
    Vector4f* result = ToAxisAngle();
    (*axis) = result->xyz();
    (*angle) = &result->w;
}

/// <summary>
/// Deconstruct quaternion into Forward and Up vectors
/// </summary>
/// <param name="qOrientation"></param>
/// <param name="newForwardVector"></param>
/// <param name="newUpVector"></param>
void Quaternion::DeconstructQuaternion(Vector3f** newForwardVector, Vector3f** newUpVector)
{
    DeconstructQuaternion(this, newForwardVector, newUpVector);
}

/// <summary>
/// Deconstruct quaternion into Forward and Up vectors
/// </summary>
/// <param name="qOrientation"></param>
/// <param name="newForwardVector"></param>
/// <param name="newUpVector"></param>
void Quaternion::DeconstructQuaternion(Quaternion* qOrientation, Vector3f** newForwardVector, Vector3f** newUpVector)
{
    // How to update local Forward and Up vectors given current Quaternion rotation:
    Vector3f* worldUp = Vector3f::Up;
    Vector3f* worldForward = Vector3f::Forward;

    (*newForwardVector) = Multiply(qOrientation, (Vector3f::Scale(worldForward, -1))); // Negated direction since we are facing camera 
    (*newUpVector) = Multiply(qOrientation, worldUp);
}

Quaternion* Quaternion::LookRotation(Vector3f* lookAt, Vector3f* up)
{
    /*Vector forward = lookAt->Normalized();
Vector right = Vector::Cross(up->Normalized(), forward);
Vector up = Vector::Cross(forward, right);*/

    Vector3f* forward = lookAt->Normalised();
    //Vector::OrthoNormalize(&up, &forward); // Keeps up the same, make forward orthogonal to up
    Vector3f* right = Vector3f::Cross(up, forward);

    Quaternion* ret = new Quaternion();
    ret->w = sqrt(1.0f + right->x + up->y + forward->z) * 0.5f;
    float w4_recip = 1.0f / (4.0f * ret->w);
    ret->x = (forward->y - up->z) * w4_recip;
    ret->y = (right->z - forward->x) * w4_recip;
    ret->z = (up->x - right->y) * w4_recip;

    return ret;
}

Quaternion* Quaternion::Euler(float x, float y, float z)
{
    // Assuming the angles are in radians->
    float c1 = cos(x / 2.0f);
    float s1 = sin(x / 2.0f);
    float c2 = cos(y / 2.0f);
    float s2 = sin(y / 2.0f);
    float c3 = cos(z / 2.0f);
    float s3 = sin(z / 2.0f);
    float c1c2 = c1 * c2;
    float s1s2 = s1 * s2;
    Quaternion* q = new Quaternion();
    q->w = c1c2 * c3 - s1s2 * s3;
    q->x = c1c2 * s3 + s1s2 * c3;
    q->y = s1 * c2 * c3 + c1 * s2 * s3;
    q->z = c1 * s2 * c3 - s1 * c2 * s3;
    return q;
}

Quaternion* Quaternion::FromAxisAngle(Vector3f* axis, float angle)
{
    if (axis->MagnitudeSquared() == 0.0f)
    {
        return Identity();
    }

    Quaternion* result = Identity();

    angle *= 0.5f;
    axis = axis->Normalise();
    Vector3f* scaled_axis = Vector3f::Scale(axis, (float)sin(angle));
    result->x = scaled_axis->x;
    result->y = scaled_axis->y;
    result->z = scaled_axis->z;
    result->w = (float)cos(angle);
    result = result->Normalised();

    return result;
}

void Quaternion::ToAxisAngle(Vector3f** axis, float** angle)
{
    Vector4f* result = ToAxisAngle();
    (*axis) = result->xyz();
    (*angle) = &result->w;
}

Vector4f* Quaternion::ToAxisAngle()
{
    Quaternion* q = this;

    if (abs(q->w) > 1.0f)
    {
        q->Normalise();
    }


    Vector4f* result = new Vector4f();

    result->w = 2.f * acos(q->w);

    float scale = sqrt(1.0f - q->w * q->w);

    if (scale > 0.0001f)
    {
        Vector3f* a = q->xyz();
        Vector3f* b = new Vector3f(a->x * (1.0f / scale), a->y * (1.0f / scale), a->z * (1.0f / scale));
        result->xyz(b);
    }
    else
    {
        // This occurs when the angle is zero-> 
        // Not a problem: just set an arbitrary normalized axis->
        result->xyz(Vector3f::UnitX);
    }

    return result;
}

Quaternion* Quaternion::Slerp(Quaternion* left, Quaternion* right, float ratio)
{
    Quaternion* result = new Quaternion(0, 0, 0, 1);
    float dot = (left->w * right->w) + (left->x * right->x) + (left->y * right->y) + (left->z * right->z);
    float blendI = 1.0f - ratio;
    if (dot < 0)
    {
        result->w = blendI * left->w + ratio * -right->w;
        result->x = blendI * left->x + ratio * -right->x;
        result->y = blendI * left->y + ratio * -right->y;
        result->z = blendI * left->z + ratio * -right->z;
    }
    else 
    {
        result->w = blendI * left->w + ratio * right->w;
        result->x = blendI * left->x + ratio * right->x;
        result->y = blendI * left->y + ratio * right->y;
        result->z = blendI * left->z + ratio * right->z;
    }
    result->Normalise();
    return result;
}

Quaternion* Quaternion::Conjugate()
{
    Vector3f* result;
    result = new Vector3f(-x, -y, -z);
    return new Quaternion(result, w);
}

Quaternion* Quaternion::Normalised()
{
    Quaternion* norm = new Quaternion(xyzw());
    float scale = 1.0f / norm->Magnitude();
    norm->xyzw(Vector4f::Scale(norm->xyzw(), scale));
    return norm;
}

void Quaternion::Normalise()
{
    float scale = 1.0f / this->Magnitude();
    xyzw(Vector4f::Scale(xyzw(), scale));
}

float Quaternion::Magnitude()
{
    return xyzw()->Magnitude();
}

float Quaternion::MagnitudeSquared()
{
    return xyzw()->MagnitudeSquared();
}

Quaternion* Quaternion::FromMatrix(Matrix4* matrix)
{
    float _w = 0.0f;
    float _x = 0.0f;
    float _y = 0.0f;
    float _z = 0.0f;
    float diagonal = matrix->m00 + matrix->m11 + matrix->m22;

    if (diagonal > 0)
    {
        float w4 = (std::sqrt(diagonal + 1.0f) * 2.0f);
        _w = w4 / 4.0f;
        _x = (matrix->m21 - matrix->m12) / w4;
        _y = (matrix->m02 - matrix->m20) / w4;
        _z = (matrix->m10 - matrix->m01) / w4;
    }
    else if ((matrix->m00 > matrix->m11) && (matrix->m00 > matrix->m22))
    {
        float x4 = (std::sqrt(1.0f + matrix->m00 - matrix->m11 - matrix->m22) * 2.0f);
        _w = (matrix->m21 - matrix->m12) / x4;
        _x = x4 / 4.0f;
        _y = (matrix->m01 + matrix->m10) / x4;
        _z = (matrix->m02 + matrix->m20) / x4;
    }
    else if (matrix->m11 > matrix->m22)
    {
        float y4 = (std::sqrt(1.0f + matrix->m11 - matrix->m00 - matrix->m22) * 2.0f);
        _w = (matrix->m02 - matrix->m20) / y4;
        _x = (matrix->m01 + matrix->m10) / y4;
        _y = y4 / 4.0f;
        _z = (matrix->m12 + matrix->m21) / y4;
    }
    else
    {
        float z4 = (std::sqrt(1.0f + matrix->m22 - matrix->m00 - matrix->m11) * 2.0f);
        _w = (matrix->m10 - matrix->m01) / z4;
        _x = (matrix->m02 + matrix->m20) / z4;
        _y = (matrix->m12 + matrix->m21) / z4;
        _z = z4 / 4.0f;
    }
    return new Quaternion(_x, _y, _z, _w);
}

Quaternion* Quaternion::Add(Quaternion* left, Quaternion* right)
{
    Vector4f* lhs = left->xyzw();
    Vector4f* rhs = right->xyzw();
    Vector4f* result = new Vector4f(lhs->x + rhs->x, lhs->y + rhs->y, lhs->z + rhs->z, lhs->w + rhs->w);
    return new Quaternion(result);
}

Quaternion* Quaternion::Add(Quaternion* left, float right)
{
    Vector4f* lhs = left->xyzw();
    Vector4f* result = new Vector4f(lhs->x + right, lhs->y + right, lhs->z + right, lhs->w + right);
    return new Quaternion(result);
}

Quaternion* Quaternion::Subtract(Quaternion* left, Quaternion* right)
{
    Vector4f* lhs = left->xyzw();
    Vector4f* rhs = right->xyzw();
    Vector4f* result = new Vector4f(lhs->x - rhs->x, lhs->y - rhs->y, lhs->z - rhs->z, lhs->w - rhs->w);
    return new Quaternion(result);
}

Quaternion* Quaternion::Subtract(Quaternion* left, float right)
{
    Vector4f* lhs = left->xyzw();
    Vector4f* result = new Vector4f(lhs->x - right, lhs->y - right, lhs->z - right, lhs->w - right);
    return new Quaternion(result);
}

Vector4f* Quaternion::Multiply(Quaternion* left, Vector4f* right)
{
    // Only works if input is a unit quaternion->
    Quaternion* norm = left->Normalised();
    Quaternion* p = new Quaternion(right);
    Quaternion* a = Multiply(p, norm->Conjugate());
    Vector4f* b = Multiply(norm, a)->xyzw();
    return b;
}

Vector3f* Quaternion::Multiply(Quaternion* left, Vector3f* right)
{
    return Multiply(left, new Vector4f(right, 0))->xyz();
}

//Quaternion* Quaternion::Multiply(Quaternion* left, Quaternion* right)
//{
//    float w;
//    w = (left->w * right->w) - Vector3f::Dot(left->xyz(), right->xyz());
//    return new Quaternion(
//        Vector3f::Add(Vector3f::Add(Vector3f::Scale(left->xyz(), right->w),
//            Vector3f::Scale(right->xyz(), left->w)),
//            Vector3f::Cross(left->xyz(), right->xyz())),
//        w
//    );
//}



Quaternion* Quaternion::Multiply(Quaternion* left, Quaternion* right)
{
    Vector3f* v1 = new Vector3f(left->x, left->y, left->z);
    Vector3f* v2 = new Vector3f(right->x, right->y, right->z);

    Vector3f* cross = Vector3f::Cross(v1, v2);                   // v x v'
    float dot = Vector3f::Dot(v1, v2);                         // v -> v'

    Vector3f* v3 = Vector3f::Add(cross, Vector3f::Add(
        Vector3f::Scale(v2, left->w), Vector3f::Scale(v1, right->w)
    ));   // v x v' + sv' + s'v

    Quaternion* result;

    result = new Quaternion(left->w * right->w - dot, v3->x, v3->y, v3->z);

    return result;
    //Quaternion* result;
    //result = new Quaternion(
    //    Vector3f::Add(Vector3f::Add(Vector3f::Scale(left->xyz(), right->w), Vector3f::Scale(right->xyz(), left->w)), Vector3f::Cross(left->xyz(), right->xyz())),
    //    left->w * right->w - Vector3f::Dot(left->xyz(), right->xyz()));
    //return result;
}

Quaternion* Quaternion::Scale(Quaternion* quaternion, float scale)
{
    return new Quaternion(
        quaternion->x * scale,
        quaternion->y * scale,
        quaternion->z * scale,
        quaternion->w * scale
    );
}

Quaternion* Quaternion::Divide(Quaternion* quaternion, float divider)
{
    return new Quaternion(
        quaternion->x / divider,
        quaternion->y / divider,
        quaternion->z / divider,
        quaternion->w / divider
    );
}

Quaternion* Quaternion::operator+(Quaternion* right) const {
    Quaternion* result;
    result = Add((Quaternion*)this, right);
    return result;
}

Quaternion* Quaternion::operator+(float right) const {
    Quaternion* result;
    result = Add((Quaternion*)this, right);
    return result;
}

Quaternion* Quaternion::operator-(Quaternion* right) const {
    Quaternion* result;
    result = Subtract((Quaternion*)this, right);
    return result;
}

Quaternion* Quaternion::operator-(float right) const {
    Quaternion* result;
    result = Subtract((Quaternion*)this, right);
    return result;
}

Quaternion* Quaternion::operator*(Quaternion* right) const {
    Quaternion* result;
    result = Multiply((Quaternion*)this, right);
    return result;
}

Vector3f* Quaternion::operator*(Vector3f* right) const {
    Vector3f* result;
    result = Multiply((Quaternion*)this, right);
    return result;
}

Vector2f* Quaternion::operator*(Vector2f* right) const {
    Vector3f* result;
    result = Multiply((Quaternion*)this, new Vector3f(right->x, right->y, 0.0f));
    return result->xy();
}

Quaternion* Quaternion::operator*(float right) const {
    Quaternion* result;
    result = Scale((Quaternion*)this, right);
    return result;
}

Quaternion* Quaternion::operator/(float right) const {
    Quaternion* result;
    result = Divide((Quaternion*)this, right); // Is actually possible to divide two quaternions but not sure how->
    return result;
}