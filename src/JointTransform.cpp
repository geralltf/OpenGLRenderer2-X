#include "JointTransform.h"
//#include "AnimatedModelLoader.h"

Matrix4* JointTransform::getLocalTransform()
{
	Matrix4* m = rotation->ToRotationMatrix();
	Matrix4* m2 = Matrix4::Identity();
	m2->SetTranslation(this->position);
	m = Matrix4::Multiply(m, m2);
	return m;
}

JointTransform* JointTransform::interpolate(JointTransform* frameA, JointTransform* frameB, float progression)
{
	Vector3f* pos = Vector3f::Lerp(frameA->position, frameB->position, progression);

	Quaternion* _rotation = Quaternion::Slerp(frameA->rotation, frameB->rotation, progression);

	Matrix4* m = _rotation->ToRotationMatrix();
	Matrix4* m2 = Matrix4::Identity();
	m2->SetTranslation(pos);
	m = Matrix4::Multiply(m, m2);

	JointTransform* inbetween  = new JointTransform(pos, _rotation, m);
	return inbetween;
}