#ifndef SKYBOX_H
#define SKYBOX_H

#include "Cubemap.h"
#include "Transform.h"
#include "Vao.h"
#include "ShaderProgram.h"
#include "UniformMatrix.h"
#include "UniformSampler.h"
#include "OpenGlUtils.h"

class Skybox 
{
private:
	Texture* cubemap;
	Vao* vao;
	ShaderProgram* shader;

	UniformMatrix* projectionMatrix = new UniformMatrix(new std::string("projectionMatrix"));
	UniformMatrix* viewMatrix = new UniformMatrix(new std::string("viewMatrix"));
	//UniformMatrix* modelMatrix = new UniformMatrix(new std::string("modelMatrix"));
	UniformSampler* cubeMap = new UniformSampler(new std::string("cubemap"));

	unsigned int _TEST_VAO;
	unsigned int _TEST_EBO;
	unsigned int _TEST_VBO;
	unsigned int _TEST_VBO_TEXCOORD;
	unsigned int _TEST_VBO_NORMAL;

	std::vector<GLfloat>* vertices_data;
public:
	Skybox(std::string* texFileRightPosX, std::string* texFileLeftNegX,
		std::string* texFileTopPosY, std::string* texFileBottomNegY,
		std::string* texFileBackPosZ, std::string* texFileFrontNegZ);

	~Skybox();

	void Render(Transform* cameraTransform, Matrix4* projection);
};

#endif