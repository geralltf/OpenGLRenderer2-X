//#include <cmath>
#include <algorithm>
#include <stdlib.h>
#include <cmath>
#include "float.h"
#include "MathHelpers.h"
#include "Vector2f.h"
#include "Vector2i.h"
#include "Vector3f.h"


// Two methods to generate tangent basis vectors.

void TriangleTangentSpace(Vector3f* v0, Vector3f* v1, Vector3f* v2,
	Vector2f* uv1, Vector2f* uv2, Vector2f* uv3,
	Vector3f** tangent, Vector3f** bitangent)
{
	// Tangent space basis vectors.
	// Calculate the tangent and bitangent vectors for the current triangle.
	Vector3f* edge1 = Vector3f::Subtract(v1, v0);
	Vector3f* edge2 = Vector3f::Subtract(v2, v0);

	Vector2f* deltaUV1 = Vector2f::Subtract(uv2, uv1);
	Vector2f* deltaUV2 = Vector2f::Subtract(uv3, uv1);

	float f = 1.0f / (deltaUV1->x * deltaUV2->y - deltaUV2->x * deltaUV1->y);

	(*tangent)->x = f * (deltaUV2->y * edge1->x - deltaUV1->y * edge2->x);
	(*tangent)->y = f * (deltaUV2->y * edge1->y - deltaUV1->y * edge2->y);
	(*tangent)->z = f * (deltaUV2->y * edge1->z - deltaUV1->y * edge2->z);
	(*tangent) = (*tangent)->Normalise();

	(*bitangent)->x = f * (-deltaUV2->x * edge1->x + deltaUV1->x * edge2->x);
	(*bitangent)->y = f * (-deltaUV2->x * edge1->y + deltaUV1->x * edge2->y);
	(*bitangent)->z = f * (-deltaUV2->x * edge1->z + deltaUV1->x * edge2->z);
	(*bitangent) = (*bitangent)->Normalise();
}

//void ComputeTangentBasis(Vector3f* P0, Vector3f* P1, Vector3f* P2,
//	Vector2f* UV0, Vector2f* UV1, Vector2f* UV2,
//	Vector3f* normal, Vector3f** tangent, Vector3f** binormal)
//{
//	Vector3f* e0 = Vector3f::Subtract(P1, P0);
//	Vector3f* e1 = Vector3f::Subtract(P2, P0);
//
//	normal = Vector3f::Cross(e0, e1);
//	//using Eric Lengyel's approach with a few modifications
//	//from Mathematics for 3D Game Programmming and Computer Graphics
//	// want to be able to trasform a vector in Object Space to Tangent Space
//	// such that the x-axis cooresponds to the 's' direction and the
//	// y-axis corresponds to the 't' direction, and the z-axis corresponds
//	// to <0,0,1>, straight up out of the texture map
//
//	//let P = v1 - v0
//	Vector3f* P = Vector3f::Subtract(P1, P0);
//	//let Q = v2 - v0
//	Vector3f* Q = Vector3f::Subtract(P2, P0);
//	float s1 = UV1->x - UV0->x;
//	float t1 = UV1->y - UV0->y;
//	float s2 = UV2->x - UV0->x;
//	float t2 = UV2->y - UV0->y;
//
//
//	//we need to solve the equation
//	// P = s1*T + t1*B
//	// Q = s2*T + t2*B
//	// for T and B
//
//
//	//this is a linear system with six unknowns and six equatinos, for TxTyTz BxByBz
//	//[px,py,pz] = [s1,t1] * [Tx,Ty,Tz]
//	// qx,qy,qz     s2,t2     Bx,By,Bz
//
//	//multiplying both sides by the inverse of the s,t matrix gives
//	//[Tx,Ty,Tz] = 1/(s1t2-s2t1) *  [t2,-t1] * [px,py,pz]
//	// Bx,By,Bz                      -s2,s1	    qx,qy,qz  
//
//	//solve this for the unormalized T and B to get from tangent to object space
//
//	float tmp = 0.0f;
//	if (fabsf(s1 * t2 - s2 * t1) <= 0.0001f)
//	{
//		tmp = 1.0f;
//	}
//	else
//	{
//		tmp = 1.0f / (s1 * t2 - s2 * t1);
//	}
//
//	(*tangent)->x = (t2 * P->x - t1 * Q->x) * tmp;
//	(*tangent)->y = (t2 * P->y - t1 * Q->y) * tmp;
//	(*tangent)->z = (t2 * P->z - t1 * Q->z) * tmp;
//
//	//(*tangent) = (*tangent) * tmp;
//
//	(*binormal)->x = (s1 * Q->x - s2 * P->x) * tmp;
//	(*binormal)->y = (s1 * Q->y - s2 * P->y) * tmp;
//	(*binormal)->z = (s1 * Q->z - s2 * P->z) * tmp;
//
//	//binormal = binormal * tmp;
//
//	normal = normal->Normalise();
//	Vector3f* t = *tangent;
//	Vector3f* bitangent = *binormal;
//	(*tangent) = t->Normalise();
//	(*binormal) = bitangent->Normalise();
//}

float cube_root(float value)
{
	return std::pow(value, 1.0f / 3.0f);
}

Vector3f* ScreenSpaceToOrthographic(Vector2i* screen, Vector2f* screenSize, Vector2f* objSize)
{
	// Orthographic matrix must be configured like this for this conversion to work in the same coordinate space.
	// quadProj = Matrix4::Orthographic(-1, 1, -1, 1, -1.0f, 1.0f);
	float sizeX = (objSize->x / screenSize->x);
	float sizeY = (objSize->y / screenSize->y);
	float halfX = sizeX * 0.25f;
	float halfY = sizeY * 0.25f;

	Vector2f* normalised = new Vector2f((screen->x / screenSize->x), (screen->y / screenSize->y));
	Vector3f* orthoPosition = new Vector3f(((normalised->x - halfX) * 2.0f) - 1.0f, ((1.0f - normalised->y - halfY) * 2.0f) - 1.0f, -1.0f);

	return orthoPosition;
}

Vector3f* ScreenSpaceToOrthographic(Vector2f* screenNormalised, Vector2f* screenSize, Vector2f* objSize)
{
	// TODO: BUGGY: Scale of objects are erroneous 
	// Orthographic matrix must be configured like this for this conversion to work in the same coordinate space.
	// quadProj = Matrix4::Orthographic(-1, 1, -1, 1, -1.0f, 1.0f);
	float sizeX = (objSize->x / screenSize->x);
	float sizeY = (objSize->y / screenSize->y);
	float halfX = sizeX * 0.25f;
	float halfY = sizeY * 0.25f;

	// Coordinates are bound to the top left corner.
	//TODO: enable referencing from other corners
	Vector3f* orthoPosition = new Vector3f(((screenNormalised->x + halfX) * 2.0f) - 1.0f, ((1.0f - screenNormalised->y - halfY) * 2.0f) - 1.0f, -1.0f);
	//Vector3f* orthoPosition = new Vector3f(((screenNormalised->x) * 2.0f) - 1.0f, ((1.0f - screenNormalised->y) * 2.0f) - 1.0f, -1.0f);

	return orthoPosition;
}

float ClampF(float value, float min, float max)
{
	return std::max(std::min(value, max), min);
}

Vector2f* Clamp(Vector2f* uv)
{
	Vector2f* clamped = new Vector2f(uv->x, uv->y);

	clamped->x = std::max(std::min(clamped->x, 1.0f), 0.0f);
	clamped->y = std::max(std::min(clamped->y, 1.0f), 0.0f);

	return clamped;
}

Vector3f* Wrap(Vector2f* uv)
{
	float sphereRadius = 1.0;
	//TODO: Might want to look into Toroidal mapping for UV coordinates (which should handle 2D wrapping).

	// Map 3D UV Sphere to 2D uv coordinate:
	// u = 0.5 + ATan2(z,x)/twopi
	// v = 0.5 - ASin(y) / pi

	// Inverse function of above is Mercator projection/spherical wrapping:

	// https://en.wikipedia.org/wiki/Mercator_projection
	float longitude = uv->x / sphereRadius;
	float latitude = (2.0 * std::atan(std::exp(uv->y / sphereRadius))) - PiOverTwo;

	Vector3f* xyz = new Vector3f(
		sphereRadius * cos(latitude) * cos(longitude),
		sphereRadius * cos(latitude) * sin(longitude),
		sphereRadius * sin(latitude)
	);

	return xyz;
}

Vector2f* NormaliseTexelCoord(Vector2f* uv, TexelMode texelMode)
{
	Vector2f* normalised = uv;
	switch (texelMode)
	{
	case TexelMode::TexelMode_Clamp:
		normalised = Clamp(uv);
		break;
	case TexelMode::TexelMode_Wrap:
		normalised = Wrap(uv)->xy();
		break;
	}
	return normalised;
}

Vector2i* ClampImageSpace(Vector2i* texelCoord, Vector2i* rectBounds)
{
	Vector2i* clamped = new Vector2i(
		(int)std::max(std::min((double)texelCoord->x, rectBounds->x - 1.0), 0.0),
		(int)std::max(std::min((double)texelCoord->y, rectBounds->y - 1.0), 0.0)
	);
	return clamped;
}

// MathHelpers.cpp
ColourRGBA* MathHelpers::ToColour(Vector4f* v)
{
    ColourRGBA* result = new ColourRGBA(v->w, v->x, v->y, v->z);
    return result;
}

Vector4f* MathHelpers::ToVector(ColourRGBA* c)
{
    Vector4f* result = new Vector4f(c->r, c->g, c->b, c->a);
    return result;
}
Vector3f* MathHelpers::ConvertColourToNormalSpace(Vector3f* colour)
{
	// Convert from 0 and 1 to -1, 1.
	Vector3f* normalCoord = new Vector3f((2 * colour->x) - 1, (2 * colour->y) - 1, (2 * colour->z) - 1);

	return normalCoord;
}
Vector3f* MathHelpers::ConvertNormalToColourSpace(Vector3f* normal)
{
	//if (normal.x < 0) normal.x *= -1;  // normals must be in 0 - 1 range not (-1 to 1)
	//if (normal.y < 0) normal.y *= -1;

	Vector3f* N = new Vector3f(normal->x, normal->y, normal->z);
	N = Vector3f::Add(N, new Vector3f(1.0f, 1.0f, 1.0f));
	N = N->Normalised();
	return N;
}

Vector3f* MathHelpers::RandomPointInCube()
{
	return GetRandomPointInCube();
}

Vector3f* MathHelpers::RandomPointInUnitSphere()
{
	return GetRandomPointInSphere();
}

Vector3f* MathHelpers::RandomPointInFrontOfPlane()
{
	return GetRandomPointInFrontOfPlane();
}

Vector3f* MathHelpers::GetRandomPointInFrontOfPlane()
{
	return GetRandomPointInFrontOfPlane(0.00001f);
}

Vector3f* MathHelpers::GetRandomPointInFrontOfPlane(float zOffset)
{
	Vector3f* point = new Vector3f(0.0f, 0.0f, 0.0f);
	point->x = (2 * RandomFloat() - 0.5f);
	point->y = (2 * RandomFloat() - 0.5f);
	point->z = (RandomFloat() + zOffset);
	return point;
}

Vector3f* MathHelpers::GetRandomPointInCube()
{
	// return RandomPointInUnitSphere;

	return new Vector3f(NormaliseBetweenNegPve(RandomFloat()),
		NormaliseBetweenNegPve(RandomFloat()),
		NormaliseBetweenNegPve(RandomFloat()));
}

int MathHelpers::Clamp(int value, int min, int max)
{
	int v = value;
	if (value < min) v = min;
	if (value > max) v = max;
	return v;
}

float MathHelpers::Clamp(float value, float min, float max)
{
	float v = value;
	if (value < min) v = min;
	if (value > max) v = max;
	return v;
}

//TODO: kinda belongs in each vector class
Vector3f* MathHelpers::ClampVector(Vector3f* v, float min, float max)
{
	return new Vector3f(Clamp(v->x, min, max), Clamp(v->y, min, max), Clamp(v->z, min, max));
}
Vector3f* MathHelpers::ClampVector(Vector3f* v, float min, Vector3f* max)
{
	return new Vector3f(Clamp(v->x, min, max->x), Clamp(v->y, min, max->y), Clamp(v->z, min, max->z));
}
Vector2f* MathHelpers::ClampVector(Vector2f* v, float min, float max)
{
	return new Vector2f(Clamp(v->x, min, max), Clamp(v->y, min, max));
}
Vector2f* MathHelpers::ClampVector(Vector2f* v, float min, Vector2f* max)
{
	return new Vector2f(Clamp(v->x, min, max->x), Clamp(v->y, min, max->y));
}
Vector2i* MathHelpers::ClampVector(Vector2i* v, int min, int max)
{
	return new Vector2i(Clamp(v->x, min, max), Clamp(v->y, min, max));
}
Vector2i* MathHelpers::ClampVector(Vector2i* v, int min, Vector2i* max)
{
	return new Vector2i(Clamp(v->x, min, max->x), Clamp(v->y, min, max->y));
}
//TODO: kinda belongs in each vector class
float MathHelpers::Lerp(float left, float right, float ratio)
{
	float result;
	result = left + ((right - left) * ratio);
	return result;
}

Vector2f* MathHelpers::Lerp(Vector2f* left, Vector2f* right, float ratio)
{
	Vector2f* result = new Vector2f(0.0f, 0.0f);
	result->x = left->x + ((right->x - left->x) * ratio);
	result->y = left->y + ((right->y - left->y) * ratio);
	return result;
}

Vector3f* MathHelpers::Lerp(Vector3f* left, Vector3f* right, float ratio)
{
	Vector3f* result = new Vector3f(0.0f, 0.0f, 0.0f);
	result->x = left->x + ((right->x - left->x) * ratio);
	result->y = left->y + ((right->y - left->y) * ratio);
	result->z = left->z + ((right->z - left->z) * ratio);
	return result;
}

//Vector4 MathHelpers::Lerp(Vector4 left, Vector4 right, float ratio)
//{
//	Vector4 result;
//	result.x = left.x + ((right.x - left.x) * ratio);
//	result.y = left.y + ((right.y - left.y) * ratio);
//	result.z = left.z + ((right.z - left.z) * ratio);
//	result.w = left.w + ((right.w - left.w) * ratio);
//	return result;
//}

/// <summary>
/// Normalise value between -1 and 1.
/// </summary>
float MathHelpers::NormaliseBetweenNegPve(float value)
{
	return (value - 0.5f) * 2;
}

float MathHelpers::RandomFloat()
{
	return ((float)rand()) / (float)RAND_MAX;
}

float MathHelpers::Range(float min, float max) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = max - min;
	float r = random * diff;
	return min + r;
}

Vector3f* MathHelpers::GetRandomPointInSphere(float radius)
{
	float v = RandomFloat();

	float theta = RandomFloat() * TwoPi;
	float phi = acos(2 * v - 1);

	float x = (radius * cos(theta) * sin(phi));
	float y = (radius * sin(theta) * sin(phi));
	float z = (radius * cos(phi));

	return new Vector3f(x, y, z);
}

Vector3f* MathHelpers::GetPointInSphere(float radius, float theta, float phiValue)
{
	float phi = acos(2 * phiValue - 1);

	float x = (radius * cos(theta) * sin(phi));
	float y = (radius * sin(theta) * sin(phi));
	float z = (radius * cos(phi));

	return new Vector3f(x, y, z);
}