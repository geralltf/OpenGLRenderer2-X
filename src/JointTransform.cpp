#include "JointTransform.h"

Matrix4* JointTransform::getLocalTransform()
{
	Matrix4* m = Matrix4::Identity();
	m->SetTranslation(this->position);
	m = Matrix4::Multiply(m, rotation->RotationMatrix());
	return m;
}

JointTransform* JointTransform::interpolate(JointTransform* frameA, JointTransform* frameB, float progression)
{
	Vector3f* pos = Vector3f::Lerp(frameA->position, frameB->position, progression);

	Quaternion* rotation = Quaternion::Slerp(frameA->rotation, frameB->rotation, progression);

	Matrix4* m = Matrix4::Identity();
	m->Translate(pos);
	m = Matrix4::Multiply(m, rotation->RotationMatrix());

	JointTransform* inbetween  = new JointTransform(pos, rotation);
	return inbetween;
}