#include "Vbo.h"

Vbo::Vbo() : vboId(0), type(-1)
{

}

Vbo::Vbo(GLuint vboId, GLuint type)
{
	this->vboId = vboId;
	this->type = type;
}

Vbo::~Vbo()
{
	glDeleteBuffers(1, &vboId);
}

Vbo* Vbo::create(GLuint type)
{
	GLuint id;
	glGenBuffers(1, &id);
	Vbo* result = new Vbo(id, type);
	return result;
}

void Vbo::bind()
{
	glBindBuffer(type, vboId);
}

void Vbo::unbind()
{
	glBindBuffer(type, 0);
}

void Vbo::storeData(std::vector<int>* data)
{
	if (data->size() == 0) return;
	int* arr = new int[data->size()];
	for (int i = 0; i < data->size(); i++)
	{
		arr[i] = data->at(i);
	}
	glBufferData(type, sizeof(int) * data->size(), arr, GL_STATIC_DRAW);
}

void Vbo::storeData(std::vector<float>* data)
{
	if (data->size() == 0) return;
	float* arr = new float [data->size()];
	for (int i = 0; i < data->size(); i++)
	{
		arr[i] = data->at(i);
	}
	glBufferData(type, sizeof(GLfloat) * data->size(), arr, GL_STATIC_DRAW);
}

void Vbo::storeData(std::vector<int*>* data)
{
	if (data->size() == 0) return;
	int* arr = new int[data->size()];
	for (int i = 0; i < data->size(); i++)
	{
		arr[i] = *data->at(i);
	}
	glBufferData(type, sizeof(int) * data->size(), arr, GL_STATIC_DRAW);
}

void Vbo::storeData(std::vector<float*>* data)
{
	if (data->size() == 0) return;
	float* arr = new float[data->size()];
	for (int i = 0; i < data->size(); i++)
	{
		arr[i] = *data->at(i);
	}
	glBufferData(type, sizeof(GLfloat) * data->size(), arr, GL_STATIC_DRAW);
}

void Vbo::storeData(std::vector<unsigned int>* data)
{
	if (data->size() == 0) return;
	unsigned int* arr = new unsigned int[data->size()];
	for (int i = 0; i < data->size(); i++)
	{
		arr[i] = data->at(i);
	}
	glBufferData(type, sizeof(unsigned int) * data->size(), arr, GL_STATIC_DRAW);
}

void Vbo::storeData(std::vector<unsigned int*>* data)
{
	if (data->size() == 0) return;
	unsigned int* arr = new unsigned int[data->size()];
	for (int i = 0; i < data->size(); i++)
	{
		arr[i] = *data->at(i);
	}
	glBufferData(type, sizeof(unsigned int) * data->size(), arr, GL_STATIC_DRAW);
}