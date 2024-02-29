#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include "Vector3f.h"
#include "VertexSkinData.h"

class Vector3f;

class Vertex 
{
private:
	int NO_INDEX = -1;

	Vector3f* position;
	int textureIndex = NO_INDEX;
	int normalIndex = NO_INDEX;
	Vertex* duplicateVertex = nullptr;
	int index;
	float length;
	std::vector<Vector3f*>* tangents = new std::vector<Vector3f*>();
	Vector3f* averagedTangent = new Vector3f(0.0f, 0.0f, 0.0f);
	VertexSkinData* weightsData;

public:

	Vertex() : index(0), length(0)
	{

	}

	Vertex(int index, Vector3f* position, VertexSkinData* weightsData) 
	{
		this->index = index;
		this->weightsData = weightsData;
		this->position = position;
		this->length = 3; // 3 component float vector
	}

	VertexSkinData* getWeightsData();
	void addTangent(Vector3f* tangent);
	void averageTangents();
	Vector3f* getAverageTangent();
	int getIndex();
	float getLength();
	bool isSet();
	bool hasSameTextureAndNormal(int textureIndexOther, int normalIndexOther);
	void setTextureIndex(int textureIndex);
	void setNormalIndex(int normalIndex);
	Vector3f* getPosition();
	int getTextureIndex();
	int getNormalIndex();
	Vertex* getDuplicateVertex();
	void setDuplicateVertex(Vertex* duplicateVertex);

};

#endif