#ifndef COORDINATE_SET_H
#define COORDINATE_SET_H

//class AABB;

#include "Vector3f.h"
#include "Vector2f.h"
#include "ColourRGBA.h"
#include <vector>

class CoorinateSet
{
public:
	std::vector<Vector3f*>* Verticies;
	std::vector<Vector2f*>* TextCoords;
	std::vector<Vector3f*>* Normals;
	std::vector<ColourRGBA*>* FaceColours;
	std::vector<ColourRGBA*>* VertexColours;

	std::vector<int*>* NormalIndicies;
	std::vector<int*>* TexCoordIndicies;
};

#endif
