#ifndef XML_GEOMETRY_LOADER_H
#define XML_GEOMETRY_LOADER_H

#include <vector>
#include <GL/glew.h>
#include "VertexSkinData.h"
#include "Matrix4.h"
#include "pugixml.hpp"
#include "Vertex.h"
#include "MeshData.h"
#include "XMLHelpers.h"
#include "StringHelpers.h"
#include "Texture.h"

/**
 * Loads the mesh data for a model from a collada XML file.
 * @author Karl
 *
 */
class GeometryLoader 
{
private:
	pugi::xpath_node meshData;
	std::vector<VertexSkinData*>* vertexWeights;
	bool hasNormals;
	bool hasTexCoords;

	std::vector<GLfloat>* verticesArray;
	int verticiesCount;
	std::vector<GLfloat>* normalsArray;
	int normalsCount;
	std::vector<GLfloat>* texturesArray;
	int texCoordsCount;
	std::vector<unsigned int>* indicesArray;
	int indicesCount;
	std::vector<unsigned int>* jointIdsArray;
	int jointsCount;
	std::vector<GLfloat>* weightsArray;
	int weightsCount;
	std::vector<GLfloat>* vertexTangents;
	int vertexTangentsCount;
	std::vector<GLfloat>* vertexBiTangents;
	int vertexBiTangentsCount;

	std::vector<Vertex*>* vertices = new std::vector<Vertex*>();
	std::vector<Vector2f*>* textures = new std::vector<Vector2f*>();
	std::vector<Vector3f*>* normals = new std::vector<Vector3f*>();
	std::vector<unsigned int>* indices = new std::vector<unsigned int>();

public:
	GeometryLoader(pugi::xpath_node geometryNode, std::vector<VertexSkinData*>* vertexWeights);
	MeshData* extractModelData();

private:

	void readRawData();
	void readPositions();
	void readNormals();
	void readTextureCoords();
	void assembleVertices();
	Vertex* processVertex(int posIndex, int normIndex, int texIndex);
	std::vector<unsigned int>* convertIndicesListToArray();
	float convertDataToArrays();
	Vertex* dealWithAlreadyProcessedVertex(Vertex* previousVertex, int newTextureIndex, int newNormalIndex);
	void initArrays();
	void removeUnusedVertices();
};

#endif