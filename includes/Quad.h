#ifndef QUAD_H
#define QUAD_H

#include "Nullable.h"
#include "Vector3f.h"
#include "ColourRGBA.h"

class Quad
{
public:
	Vector3f* vertex00;
	Vector3f* vertex01;
	Vector3f* vertex10;
	Vector3f* vertex11;

	Nullable<Vector3f*>* normal00;
	Nullable<Vector3f*>* normal01;
	Nullable<Vector3f*>* normal10;
	Nullable<Vector3f*>* normal11;

	Nullable<Vector4f*>* colour00;
	Nullable<Vector4f*>* colour01;
	Nullable<Vector4f*>* colour10;
	Nullable<Vector4f*>* colour11;

	Nullable<Vector2f*>* texCoord00;
	Nullable<Vector2f*>* texCoord01;
	Nullable<Vector2f*>* texCoord10;
	Nullable<Vector2f*>* texCoord11;

	bool HasNormalPerVertex = false;
	bool HasColourPerVertex = false;
	bool HasTexCoordPerVertex = false;
	bool AutocalcNormals = false;

	Nullable<ColourRGBA*>* faceColour;

	bool HasVertexNormals() const;

	bool HasVertexColours() const;

	Quad();

	Quad(Vector3f* q0, Vector3f* q1, Vector3f* q2, Vector3f* q3);
};


#endif
