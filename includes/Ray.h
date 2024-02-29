#ifndef RAY_H
#define RAY_H

#include "Vector3f.h"

class Ray
{
public:
	Vector3f* Origin;
	Vector3f* Direction;
	float Length;

	Ray();

	Ray(Vector3f* origin, Vector3f* direction);

	Ray(Vector3f* origin, Vector3f* direction, float length);

	Ray* operator *(Matrix4* right) const
	{
		const Ray* lhs = this;
		return TransformRay((Ray*)lhs, right);
	}

	static Ray* TransformRay(Ray* ray, Matrix4* transformMatrix);
};

#endif
