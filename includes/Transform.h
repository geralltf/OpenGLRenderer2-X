#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Nullable.h"
#include "Matrix4.h"
#include <vector>

class Transform;
class Camera;

typedef Vector2i(Transform::*ProjectionFunct)(Vector3f*);

class Transform
{
public:

	//static Nullable<Transform> rootTransform; //TEST:HACK:
	Nullable<Transform*>* ParentTransform = new Nullable<Transform*>();

	std::vector<Transform*>* Children = new std::vector<Transform*>();

	/// <summary>
	/// The combined set of local transformations to apply to the object.
	/// </summary>
	Matrix4* localMatrix = Matrix4::Identity();
	Matrix4* worldMatrix;// the new combined transform matrix

	Quaternion* QOrientationLocal;
	Quaternion* QOrientationWorld;

private:

	Vector3f* forwardVector;
	Vector3f* upVector;
	float localYaw, localPitch, localRoll;
	float yaw, pitch, roll;
	Quaternion* qRotWorld;
	Matrix4* viewRotation;

public:
	float _fovScale = 1;

public:
	Transform();
	~Transform();

	Vector3f* GetLocalPosition();
	Vector3f* GetLocalScale();
	Vector3f* GetPosition();
	Vector3f* GetForwardVector();
	Vector3f* GetUpVector();
	float GetLocalYaw();
	float GetLocalPitch();
	float GetLocalRoll();
	float GetYaw();
	float GetPitch();
	float GetRoll();
	Vector3f* GetRotation();
	Vector3f* GetWorldPosition();

	void SetWorldPosition(Vector3f* position);
	void SetLocalPosition(Vector3f* value);
	void SetLocalScale(Vector3f* value);
	void SetPosition(Vector3f* value);
	void SetForwardVector(Vector3f* value);
	void SetUpVector(Vector3f* value);
	void SetLocalYaw(float yawValue);
	void SetLocalPitch(float pitchValue);
	void SetLocalRoll(float rollValue);
	void SetYaw(float yawValue);
	void SetPitch(float pitchValue);
	void SetRoll(float rollValue);


	void updatelocalVectorRotation();
	void updatelocalQuaternionRotation();
	void updateworldQuaternionRotation();


	Camera* GetCamera();

	ProjectionFunct worldToScreen();

	/// <summary>
	/// Scales a vector by the specified scale.
	/// </summary>
	void Scale(float scalar);
	void Scale(Vector3f* scale);

	void RotateX(float angleInDegrees);
	void RotateY(float angleInDegrees);
	void RotateZ(float angleInDegrees);
	void Rotate(float rotationXPitchInDegrees, float rotationYYawInDegrees, float rotationZRollInDegrees);

	/// <summary>
	/// Translates a vector by the specified translation.
	/// </summary>
	/// <param name="vector"></param>
	/// <param name="translation"></param>
	/// <returns></returns>
	void Translate(float x, float y, float z);

	/// <summary>
	/// Translates a vector by the specified translation.
	/// </summary>
	/// <param name="vector"></param>
	/// <param name="translation"></param>
	/// <returns></returns>
	void Translate(Vector3f* translation);

	Matrix4* LocalMatrix();

	void ScaleFieldOfView(float scaleFactor);

	Vector4f* TransformSRT(Vector4f* vector, Vector3f* scale, Vector3f* rotationYPR, Vector3f* translation);

	Matrix4* RecalculateWorldTransformations();

	Matrix4* RecalculateLocalToWorldMatrix();

	Vector4f* TransformLocalToWorldspace(Vector3f* localPosition);
};
#endif
