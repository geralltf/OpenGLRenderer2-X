#ifndef FACEATTRIBUTES_H
#define FACEATTRIBUTES_H

#include "Nullable.h"
#include "Enums.h"

class FaceAttributes
{
public:
	PolygonType Polygon;

	Vector3f* Origin;

	Nullable<Vector4f*>* faceColour;

	bool HasNormalPerVertex = false;
	bool HasColourPerVertex = false;

	bool AutocalcNormals = false;

	FaceAttributes() : 
		Polygon(PolygonType::PT_Triangles),
		Origin(Vector3f::ZERO),
		faceColour(new Nullable<Vector4f*>())
	{

	}
};

#endif
