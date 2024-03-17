#ifndef SPRITE_H
#define SPRITE_H

#include "Texture.h"
#include "Vao.h"
#include "ShaderProgram.h"
#include "OpenGlUtils.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

class Sprite
{
public:
	Texture* spriteTexture;
	Vao* vaoSprite;
	ShaderProgram* program;
	std::vector<unsigned int>* indicies;

	Vector3f* position;
	Vector2f* sprite_size;
	Vector3f* scale;

	Sprite(Texture* texture, ShaderProgram* shaderProgram, Vao* vao, Vector2f* spriteSize, Vector3f* position, Vector3f* scalar)
	{
		this->spriteTexture = texture;
		this->program = shaderProgram;
		this->vaoSprite = vao;
		this->sprite_size = spriteSize;
		this->position = position;
		this->scale = scalar;
		this->indicies = nullptr;
	}
	~Sprite()
	{
		delete spriteTexture;
		delete vaoSprite;
		delete program;
		delete indicies;
		delete position;
		delete sprite_size;
	}

	static Sprite* Create(std::string texture_file_name, Vector2f* sprite_size, Vector3f* sprite_position, Vector3f* scale, bool flip_vertically);

	static Sprite* Create(std::string* texture_file_name, Vector2f* sprite_size, Vector3f* sprite_position, Vector3f* scale, bool flip_vertically);

	void render(sf::RenderWindow* window);
};

#endif