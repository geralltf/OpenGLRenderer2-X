#ifndef MATH_HELPERS_H
#define MATH_HELPERS_H

#include "ColourRGBA.h"
#include "Quaternion.h"
#include "Matrix4.h"
#include "Matrix3.h"
#include "Vector4f.h"
#include "Vector3f.h"
#include "Vector2i.h"
#include "Vector2f.h"

enum TexelMode
{
	TexelMode_Clamp,
	TexelMode_Wrap
};

void TriangleTangentSpace(Vector3f* v0, Vector3f* v1, Vector3f* v2,
	Vector2f* uv1, Vector2f* uv2, Vector2f* uv3,
	Vector3f** tangent, Vector3f** bitangent);

//void ComputeTangentBasis(const Vector3f* P0, const Vector3f* P1, const Vector3f* P2,
//	const Vector2f* UV0, const Vector2f* UV1, const Vector2f* UV2,
//	Vector3f* normal, Vector3f** tangent, Vector3f** binormal);
inline void ComputeTangentBasis(Vector3f* P0, Vector3f* P1, Vector3f* P2,
	Vector2f* UV0, Vector2f* UV1, Vector2f* UV2,
	Vector3f* normal, Vector3f** tangent, Vector3f** binormal)
{
	Vector3f* e0 = Vector3f::Subtract(P1, P0);
	Vector3f* e1 = Vector3f::Subtract(P2, P0);

	normal = Vector3f::Cross(e0, e1);
	//using Eric Lengyel's approach with a few modifications
	//from Mathematics for 3D Game Programmming and Computer Graphics
	// want to be able to trasform a vector in Object Space to Tangent Space
	// such that the x-axis cooresponds to the 's' direction and the
	// y-axis corresponds to the 't' direction, and the z-axis corresponds
	// to <0,0,1>, straight up out of the texture map

	//let P = v1 - v0
	Vector3f* P = Vector3f::Subtract(P1, P0);
	//let Q = v2 - v0
	Vector3f* Q = Vector3f::Subtract(P2, P0);
	float s1 = UV1->x - UV0->x;
	float t1 = UV1->y - UV0->y;
	float s2 = UV2->x - UV0->x;
	float t2 = UV2->y - UV0->y;


	//we need to solve the equation
	// P = s1*T + t1*B
	// Q = s2*T + t2*B
	// for T and B


	//this is a linear system with six unknowns and six equatinos, for TxTyTz BxByBz
	//[px,py,pz] = [s1,t1] * [Tx,Ty,Tz]
	// qx,qy,qz     s2,t2     Bx,By,Bz

	//multiplying both sides by the inverse of the s,t matrix gives
	//[Tx,Ty,Tz] = 1/(s1t2-s2t1) *  [t2,-t1] * [px,py,pz]
	// Bx,By,Bz                      -s2,s1	    qx,qy,qz  

	//solve this for the unormalized T and B to get from tangent to object space

	float tmp = 0.0f;
	if (fabsf(s1 * t2 - s2 * t1) <= 0.0001f)
	{
		tmp = 1.0f;
	}
	else
	{
		tmp = 1.0f / (s1 * t2 - s2 * t1);
	}

	(*tangent)->x = (t2 * P->x - t1 * Q->x) * tmp;
	(*tangent)->y = (t2 * P->y - t1 * Q->y) * tmp;
	(*tangent)->z = (t2 * P->z - t1 * Q->z) * tmp;

	//(*tangent) = (*tangent) * tmp;

	(*binormal)->x = (s1 * Q->x - s2 * P->x) * tmp;
	(*binormal)->y = (s1 * Q->y - s2 * P->y) * tmp;
	(*binormal)->z = (s1 * Q->z - s2 * P->z) * tmp;

	//binormal = binormal * tmp;

	normal = normal->Normalise();
	Vector3f* t = *tangent;
	Vector3f* bitangent = *binormal;
	(*tangent) = t->Normalise();
	(*binormal) = bitangent->Normalise();
}

float cube_root(float value);

Vector3f* ScreenSpaceToOrthographic(Vector2i* screen, Vector2f* screenSize, Vector2f* objSize);
Vector3f* ScreenSpaceToOrthographic(Vector2f* screenNormalised, Vector2f* screenSize, Vector2f* objSize);

float ClampF(float value, float min, float max);

Vector2f* Clamp(Vector2f* uv);

Vector3f* Wrap(Vector2f* uv);

Vector2f* NormaliseTexelCoord(Vector2f* uv, TexelMode texelMode);

Vector2i* ClampImageSpace(Vector2i* texelCoord, Vector2i* rectBounds);


class MathHelpers
{
public:
	static ColourRGBA* ToColour(Vector4f* v);
    static Vector4f* ToVector(ColourRGBA* c);
	static Vector3f* ConvertColourToNormalSpace(Vector3f* colour);
	static Vector3f* ConvertNormalToColourSpace(Vector3f* normal);
	static Vector3f* RandomPointInCube();
	static Vector3f* RandomPointInUnitSphere();
	static Vector3f* RandomPointInFrontOfPlane();
	static Vector3f* GetRandomPointInFrontOfPlane();
	static Vector3f* GetRandomPointInFrontOfPlane(float zOffset);
	static Vector3f* GetRandomPointInCube();
	static int Clamp(int value, int min, int max);
	static float Clamp(float value, float min, float max);

	//TODO: kinda belongs in each vector class
	static Vector3f* ClampVector(Vector3f* v, float min, float max);
	static Vector3f* ClampVector(Vector3f* v, float min, Vector3f* max);
	static Vector2f* ClampVector(Vector2f* v, float min, float max);
	static Vector2f* ClampVector(Vector2f* v, float min, Vector2f* max);
	static Vector2i* ClampVector(Vector2i* v, int min, int max);
	static Vector2i* ClampVector(Vector2i* v, int min, Vector2i* max);
	//TODO: kinda belongs in each vector class
	static float Lerp(float left, float right, float ratio);

	static Vector2f* Lerp(Vector2f* left, Vector2f* right, float ratio);
	static Vector3f* Lerp(Vector3f* left, Vector3f* right, float ratio);

	//static Vector4 Lerp(Vector4 left, Vector4 right, float ratio);

	/// <summary>
	/// Normalise value between -1 and 1.
	/// </summary>
	static float NormaliseBetweenNegPve(float value);

	static float RandomFloat();

	static float Range(float min, float max);

	static Vector3f* GetRandomPointInSphere()
	{
		return GetRandomPointInSphere(1.0f);
	}

	static Vector3f* GetRandomPointInSphere(float radius);

	static Vector3f* GetPointInSphere(float radius, float theta, float phiValue);
};
#endif