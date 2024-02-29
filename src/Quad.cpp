#include "Quad.h"

Quad::Quad() :
	vertex00(Vector3f::ZERO),
	vertex01(Vector3f::ZERO),
	vertex10(Vector3f::ZERO),
	vertex11(Vector3f::ZERO),
	normal00(new Nullable<Vector3f*>()),
	normal01(new Nullable<Vector3f*>()),
	normal10(new Nullable<Vector3f*>()),
	normal11(new Nullable<Vector3f*>()),
	colour00(new Nullable<Vector4f*>()),
	colour01(new Nullable<Vector4f*>()),
	colour10(new Nullable<Vector4f*>()),
	colour11(new Nullable<Vector4f*>()),
	texCoord00(new Nullable<Vector2f*>()),
	texCoord01(new Nullable<Vector2f*>()),
	texCoord10(new Nullable<Vector2f*>()),
	texCoord11(new Nullable<Vector2f*>()),
	faceColour(new Nullable<ColourRGBA*>())
{
	
}

Quad::Quad(Vector3f* q0, Vector3f* q1, Vector3f* q2, Vector3f* q3) :
	vertex00(Vector3f::ZERO),
	vertex01(Vector3f::ZERO),
	vertex10(Vector3f::ZERO),
	vertex11(Vector3f::ZERO),
	normal00(new Nullable<Vector3f*>()),
	normal01(new Nullable<Vector3f*>()),
	normal10(new Nullable<Vector3f*>()),
	normal11(new Nullable<Vector3f*>()),
	colour00(new Nullable<Vector4f*>()),
	colour01(new Nullable<Vector4f*>()),
	colour10(new Nullable<Vector4f*>()),
	colour11(new Nullable<Vector4f*>()),
	texCoord00(new Nullable<Vector2f*>()),
	texCoord01(new Nullable<Vector2f*>()),
	texCoord10(new Nullable<Vector2f*>()),
	texCoord11(new Nullable<Vector2f*>()),
	faceColour(new Nullable<ColourRGBA*>())
{
	vertex00 = q0;
	vertex01 = q1;
	vertex10 = q2;
	vertex11 = q3;
}

bool Quad::HasVertexNormals() const
{
	return normal00->is_set() && normal01->is_set() && normal10->is_set() && normal11->is_set();
}

bool Quad::HasVertexColours() const
{
	return colour00->is_set() && colour01->is_set() && colour10->is_set() && colour11->is_set();
}