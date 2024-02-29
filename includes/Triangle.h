#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Nullable.h"
#include "Vector3f.h"
#include "ColourRGBA.h"

class Triangle // TODO: This is a TEST for just one type of polygon.
{
public:
	Vector3f* positionXStep;
	Vector3f* positionYStep;

	Vector4f* colourXStep;
	Vector4f* colourYStep;

	Vector3f* normalXStep;
	Vector3f* normalYStep;

	Vector2f* texCoordXStep;
	Vector2f* texCoordYStep;

	Vector3f* Origin;

	Vector3f* vertex00;
	Vector3f* vertex01;
	Vector3f* vertex10;

	Nullable<Vector3f*> normal00;
	Nullable<Vector3f*> normal01;
	Nullable<Vector3f*> normal10;

	Nullable<Vector4f*> colour00;
	Nullable<Vector4f*> colour01;
	Nullable<Vector4f*> colour10;

	Nullable<Vector2f*> texCoord00;
	Nullable<Vector2f*> texCoord01;
	Nullable<Vector2f*> texCoord10;

	Nullable<ColourRGBA*> faceColour;

	bool HasNormalPerVertex = false;
	bool HasColourPerVertex = false;
	bool HasTexCoordPerVertex = false;

	bool AutocalcNormals = false;

	Triangle();

	Triangle(Vector3f* t0, Vector3f* t1, Vector3f* t2);

	~Triangle();

	static Triangle* Clone(Triangle* t); // BUG:HACK: Cloning triangle because coordinates seem to be weirdly affected by transformations


	void Grad();

	Vector3f* TriangleLerp(Vector2f* uv);

	Vector3f* TriangleVertexLerp(Vector2f* uv);

	Vector3f* TriangleNormalLerp(Vector2f* uv); // if only!

	Vector4f* TriangleColourLerp(Vector2f* uv); // if only!

	bool HasVertexNormals();

	bool HasVertexColours();

	bool HasVertexTexCoords();

	Vector3f* CenterOfTriangle();

	Vector3f* GetNormal(Vector3f* vertexPosition);

	Vector3f* SurfaceNormal();

	Vector3f* SurfaceNormalFront(); // Front face normal.
	Vector3f* SurfaceNormalBack(); // Back face normal. (pointing in opposite direction)

	void SwapVectors();

	float GetArea();
	int GetHandednessI();
	bool GetHandedness();

	static float TriangleAreaTimesTwo(Vector3f* b, Vector3f* c, Vector3f* m);

	static float TriangleAreaTimesTwo(Vector2f* b, Vector2f* c, Vector2f* m);
};


#endif
