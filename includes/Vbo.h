#ifndef VBO_H
#define VBO_H

#include <vector>
#include <GL/glew.h>		// Include GLEW and new version of GL on Windows.
#include <GLFW/glfw3.h>		// GLFW helper library.

class Vbo 
{
private:
	GLuint vboId;
	GLuint type;

public:
	Vbo();
	Vbo(GLuint vboId, GLuint type);
	~Vbo();
	static Vbo* create(GLuint type);

	void bind();
	void unbind();

	void storeData(std::vector<unsigned int>* data);
	void storeData(std::vector<unsigned int*>* data);
	
	void storeData(std::vector<int>* data);
	void storeData(std::vector<float>* data);
	void storeData(std::vector<int*>* data);
	void storeData(std::vector<float*>* data);
};

#endif