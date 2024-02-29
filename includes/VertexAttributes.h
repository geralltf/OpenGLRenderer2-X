#ifndef VERTEXATTRIBUTES_H
#define VERTEXATTRIBUTES_H

#include "Nullable.h"
#include "Vector2f.h"
#include "Vector3f.h"
#include "Vector4f.h"

class VertexAttributes
{
public:
	Vector3f* Vertex;

	Nullable<Vector3f*> Normal;
	Nullable<Vector4f*> Colour;
	Nullable<Vector2f*> TextureCoordinate;

	VertexAttributes():
		Normal(Nullable<Vector3f*>()),
		Colour(Nullable<Vector4f*>()),
		TextureCoordinate(Nullable<Vector2f*>()),
		Vertex(Vector3f::ZERO)
	{
		
	}
};

#endif
