#include "Transform.h"
#include "MathHelpers.h"
#include <iostream>
//#include <mmsystem.h>


//Nullable<Transform> Transform::rootTransform = Nullable<Transform>(); //TEST:HACK:

Transform::Transform() :
	ParentTransform(new Nullable<Transform*>()),
	localMatrix(Matrix4::Identity()),
	worldMatrix(Matrix4::Identity()),
	QOrientationLocal(Quaternion::Identity()),
	QOrientationWorld(Quaternion::Identity()),
	upVector(Vector3f::Up),
	forwardVector(Vector3f::Forward),
	viewRotation(Matrix4::Identity()),
	qRotWorld(Quaternion::Identity())
{

	Children = new std::vector<Transform*>();
	//rootTransform = Nullable<Transform>(); //TEST:HACK:
}

Transform::~Transform()
{
	//delete Children;
}

Vector3f* Transform::GetLocalPosition()
{
	return localMatrix->GetTranslation();
}

Vector3f* Transform::GetLocalScale()
{
	return localMatrix->GetScale();
}

Vector3f* Transform::GetPosition()
{
	return Matrix4::TransformVector(localMatrix, GetLocalPosition());
}

Vector3f* Transform::GetForwardVector()
{
	Quaternion::DeconstructQuaternion(QOrientationLocal, &forwardVector, &upVector);

	return forwardVector;
}

Vector3f* Transform::GetUpVector()
{
	Quaternion::DeconstructQuaternion(QOrientationLocal, &forwardVector, &upVector);

	return upVector;
}

float Transform::GetLocalYaw()
{
	return localYaw;
}

float Transform::GetLocalPitch()
{
	return localPitch;
}

float Transform::GetLocalRoll()
{
	return localRoll;
}

float Transform::GetYaw()
{
	return yaw;
}
float Transform::GetPitch()
{
	return pitch;
}
float Transform::GetRoll()
{
	return roll;
}

Vector3f* Transform::GetRotation()
{
    Vector3f* result = new Vector3f(GetYaw(), GetPitch(), GetRoll());

    return result;
}

Vector3f* Transform::GetWorldPosition()
{
	return GetPosition();
}

void Transform::SetWorldPosition(Vector3f* position)
{
	SetPosition(position);
}

void Transform::SetLocalPosition(Vector3f* value)
{
	Translate(value);
}

void Transform::SetLocalScale(Vector3f* value)
{
	Scale(value);
}

void Transform::SetPosition(Vector3f* value)
{
	// TODO: TEST: World position to local position translation
	Vector3f* local = Matrix4::TransformVector(worldMatrix, value);

	SetLocalPosition(local);
}

void Transform::SetForwardVector(Vector3f* value)
{
	forwardVector = value;

	updatelocalVectorRotation();
}

void Transform::SetUpVector(Vector3f* value)
{
	upVector = value;

	updatelocalVectorRotation();
}

void Transform::SetLocalYaw(float yawValue)
{
	localYaw = yawValue;
	updatelocalQuaternionRotation();
}

void Transform::SetLocalPitch(float pitchValue)
{
	localPitch = pitchValue;
	updatelocalQuaternionRotation();
}

void Transform::SetLocalRoll(float rollValue)
{
	localRoll = rollValue;
	updatelocalQuaternionRotation();
}

void Transform::SetYaw(float yawValue)
{
	yaw = yawValue;
	updateworldQuaternionRotation();
}

void Transform::SetPitch(float pitchValue)
{
	pitch = pitchValue;
	updateworldQuaternionRotation();
}

void Transform::SetRoll(float rollValue)
{
	roll = rollValue;
	updateworldQuaternionRotation();
}


void Transform::updatelocalVectorRotation()
{
	QOrientationLocal = Quaternion::LookRotation(forwardVector, upVector);
}
void Transform::updatelocalQuaternionRotation()
{
	QOrientationLocal = Quaternion::Euler(GetLocalYaw(), GetLocalPitch(), GetLocalRoll());
}
void Transform::updateworldQuaternionRotation()
{
	QOrientationWorld = Quaternion::Euler(GetYaw(), GetPitch(), GetRoll());
}

/// <summary>
/// Scales a vector by the specified scale.
/// </summary>
void Transform::Scale(float scalar)
{
	localMatrix->Scale(Vector3f::Scale(Vector3f::ONE, scalar));
}
void Transform::Scale(Vector3f* scale)
{
	localMatrix->Scale(scale);
}

void Transform::RotateX(float angleInDegrees)
{
	localMatrix->RotateX(angleInDegrees);
}
void Transform::RotateY(float angleInDegrees)
{
	localMatrix->RotateY(angleInDegrees);
}
void Transform::RotateZ(float angleInDegrees)
{
	localMatrix->RotateZ(angleInDegrees);
}

void Transform::Rotate(float rotationXPitchInDegrees, float rotationYYawInDegrees, float rotationZRollInDegrees)
{
	Quaternion* rotation = Quaternion::Euler(rotationXPitchInDegrees, rotationYYawInDegrees, rotationZRollInDegrees);
	localMatrix = Matrix4::Multiply(rotation->RotationMatrix(), localMatrix);
}


/// <summary>
/// Translates a vector by the specified translation.
/// </summary>
/// <param name="vector"></param>
/// <param name="translation"></param>
/// <returns></returns>
void Transform::Translate(float x, float y, float z)
{
	Vector3f* transl = new Vector3f(x, y, z);
	Translate(transl);
}

/// <summary>
/// Translates a vector by the specified translation.
/// </summary>
/// <param name="vector"></param>
/// <param name="translation"></param>
/// <returns></returns>
void Transform::Translate(Vector3f* translation)
{
	localMatrix->Translate(translation);
}

Matrix4* Transform::LocalMatrix() // LocalToWorldMatrix
{
	return localMatrix;
}

void Transform::ScaleFieldOfView(float scaleFactor)
{
	if (scaleFactor > 1.0f)
	{
		_fovScale = (1.0f / _fovScale) * (1.0f / scaleFactor);
	}
	else
	{
		_fovScale = scaleFactor;
	}
}

Vector4f* Transform::TransformSRT(Vector4f* vector, Vector3f* scale, Vector3f* rotationYPR, Vector3f* translation)
{
	// Manual SRT 4x4 Matrix

	Vector4f* result = new Vector4f();


	Matrix4* matrixSRT = Matrix4::Identity();

	matrixSRT->Scale(scale);
	matrixSRT = Matrix4::Multiply(matrixSRT, Matrix4::RotationYawPitchRoll(rotationYPR->y, rotationYPR->x, rotationYPR->z));
	matrixSRT->Translate(translation);

	result = Matrix4::TransformVector(matrixSRT, vector);

	return result;
}

Matrix4* Transform::RecalculateWorldTransformations()
{
	Matrix4* combinedTransformationMatrix = Matrix4::CreateSQTMatrix(GetLocalScale(), QOrientationLocal, GetLocalPosition());

	if (ParentTransform->is_set())
	{
		// Recalculate prior transformations
		Transform* p = ParentTransform->get();

		while (p != nullptr)
		{
			Matrix4* current_transform_matrix = Matrix4::CreateSQTMatrix(p->GetLocalScale(), p->QOrientationLocal, p->GetLocalPosition());

			combinedTransformationMatrix = Matrix4::Multiply(combinedTransformationMatrix, current_transform_matrix);

			p->worldMatrix = combinedTransformationMatrix;

			if (p->ParentTransform->is_set())
			{
				p = p->ParentTransform->get();
			}
			else
			{
				p = nullptr;
			}
		}
	}

	worldMatrix = combinedTransformationMatrix;

	return combinedTransformationMatrix;
}

Matrix4* Transform::RecalculateLocalToWorldMatrix()
{
	Matrix4* localToWorld = localMatrix;

	return localToWorld;
}

Vector4f* Transform::TransformLocalToWorldspace(Vector3f* localPosition)
{
	// Transform the local position to world space
	// applying transformations from the object and its parents to derive a world position

	Vector4f* inputLocal = new Vector4f(localPosition, 1.0f);

	//Vector4 result = RecalculateLocalToWorldMatrix() * inputLocal;
	RecalculateWorldTransformations();

	Vector4f* result = worldMatrix->TransformVector(worldMatrix, inputLocal);

	result->w = 1.0f;

	return result;
}