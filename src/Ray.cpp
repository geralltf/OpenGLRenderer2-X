#include "Ray.h"

Ray::Ray()
{
	Origin = Vector3f::ZERO;
	Direction = Vector3f::Forward;
	Length = FLT_MAX;
}

Ray::Ray(Vector3f* origin, Vector3f* direction)
{
	Origin = origin;
	Direction = direction;
	Length = FLT_MAX;
}

Ray::Ray(Vector3f* origin, Vector3f* direction, float length)
{
	Origin = origin;
	Direction = direction;
	Length = length;
}

Ray* Ray::TransformRay(Ray* ray, Matrix4* transformMatrix)
{
	Ray* r = new Ray();
	r->Origin = Matrix4::TransformVector(transformMatrix, ray->Origin);
	r->Direction = Matrix4::TransformVector(transformMatrix, ray->Direction);
	//r.Origin = ray.Origin.TransformVector(transformMatrix);
	//r.Direction = ray.Direction.TransformNormal(transformMatrix);
	return r;
}
