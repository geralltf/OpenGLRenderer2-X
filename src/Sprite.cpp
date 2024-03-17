#include "Sprite.h"

Sprite* Sprite::Create(std::string texture_file_name, Vector2f* sprite_size, Vector3f* sprite_position, Vector3f* scale, bool flip_vertically)
{
	return Create(&texture_file_name, sprite_size, sprite_position, scale, flip_vertically);
}

Sprite* Sprite::Create(std::string* texture_file_name, Vector2f* sprite_size, Vector3f* sprite_position, Vector3f* scale, bool flip_vertically)
{
	Texture* spriteTexture = Texture::LoadTexture(texture_file_name)->Anisotropic()->ClampEdges()->NearestFiltering()->Create(flip_vertically);

	ShaderProgram* program = new ShaderProgram("Shaders/screenSprite_vs.glsl", "Shaders/screenSprite_fs.glsl");

	Vao* vaoSprite;

	std::vector<GLfloat>* vertices = new std::vector<GLfloat>();
	GLfloat v = 0.0f;
	GLfloat v2 = 1.0f;

	vertices->push_back(v);
	vertices->push_back(v);
	vertices->push_back(v);

	vertices->push_back(v2);
	vertices->push_back(v);
	vertices->push_back(v);
	vertices->push_back(v2);
	vertices->push_back(v2);
	vertices->push_back(v);

	vertices->push_back(v);
	vertices->push_back(v2);
	vertices->push_back(v);

	std::vector<GLfloat>* texCoords = new std::vector<GLfloat>();
	GLfloat f = 0.0f;
	GLfloat f2 = 1.0f;

	texCoords->push_back(f);
	texCoords->push_back(f2);
	texCoords->push_back(f);
	texCoords->push_back(f);
	texCoords->push_back(f2);
	texCoords->push_back(f2);
	texCoords->push_back(f);
	texCoords->push_back(f2);

	std::vector<unsigned int>* indicies;

	indicies = new std::vector<unsigned int>();
	unsigned int i = 0;
	unsigned int i2 = 1;
	unsigned int i3 = 2;
	unsigned int i4 = 3;

	indicies->push_back(i);
	indicies->push_back(i2);
	indicies->push_back(i3);
	indicies->push_back(i4);

	vaoSprite = Vao::create();
	vaoSprite->bind();
	vaoSprite->createIndexBuffer(indicies);
	vaoSprite->createAttribute(0, vertices, 3);
	vaoSprite->createAttribute(1, texCoords, 2);
	vaoSprite->unbind();

	Sprite* sprite = new Sprite(spriteTexture, program, vaoSprite, sprite_size, sprite_position, scale);
	sprite->indicies = indicies;
	return sprite;
}

void Sprite::render(sf::RenderWindow* window)
{
	//Vector2f* spriteSize = new Vector2f(64, 64); // size of the sprite in pixels
	Vector2i* screenSpacePosition = new Vector2i(this->position->x, this->position->y);
	Vector2f* screenSize = new Vector2f((float)window->getSize().x, (float)window->getSize().y);
	//Vector3f* position = ScreenSpaceToOrthographic(mouse, screenSize, cursorSize);
	Vector3f* position2 = new Vector3f(
		((float)screenSpacePosition->x / screenSize->x) - 0.05f,
		(1.0f - ((float)screenSpacePosition->y / screenSize->y)) - 0.05f,
		-2.0f
	);
	Matrix4* model = Matrix4::Identity();

	float sizeX = ((this->sprite_size->x / (float)window->getSize().x));
	float sizeY = ((this->sprite_size->y / (float)window->getSize().y));

	Matrix4* scalarMatrix = Matrix4::Scale(this->scale->x, this->scale->y, this->scale->z);
	
	model = Matrix4::Multiply(model, scalarMatrix);
	model->Translate(position2);

	Matrix4* quadModelView = model;
	Matrix4* quadView;
	quadView = Matrix4::Identity(); // Dont use camera transform local matrix since the sprite is meant to follow the user interface on screen as the player moves.
	Matrix4* quadProj;
	quadProj = Matrix4::Orthographic(0.0f, 1.0f, 0.0f, 1.0f, 0.1f, 1000.0f); // Stick to using screen space transform for 2D user interface and 2D sprites.

	Matrix4* MVP = Matrix4::Multiply(Matrix4::Multiply(quadProj, quadView), quadModelView);

	float* arrMVP = MVP->ToArray();
	float* arrP = quadProj->ToArray();
	float* arrV = quadView->ToArray();
	float* arrM = quadModelView->ToArray();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	OpenGlUtils::EnableAlphaBlending(); // EnableAlphaBlending
	OpenGlUtils::EnableDepthTesting(false);
	glUseProgram(program->programID);
	glUniformMatrix4fv(glGetUniformLocation(program->programID, "MVP"), 1, GL_FALSE, arrMVP);
	glUniformMatrix4fv(glGetUniformLocation(program->programID, "projectionMatrix"), 1, GL_FALSE, arrP);
	glUniformMatrix4fv(glGetUniformLocation(program->programID, "viewMatrix"), 1, GL_FALSE, arrV);
	glUniformMatrix4fv(glGetUniformLocation(program->programID, "modelMatrix"), 1, GL_FALSE, arrM);
	glUniform2f(glGetUniformLocation(program->programID, "textureSize2"), sprite_size->x, sprite_size->y);
	glUniform1i(glGetUniformLocation(program->programID, "spriteTexture"), 0);

	glActiveTexture(GL_TEXTURE0);
	spriteTexture->bindToUnit(0);
	if (vaoSprite != nullptr)
	{
		vaoSprite->bind();
		vaoSprite->binder(0, 1);
		glDrawElements(GL_QUADS, indicies->size(), GL_UNSIGNED_INT, nullptr);
		vaoSprite->unbinder(0, 1);
		vaoSprite->unbind();
		glUseProgram(0);
	}

	delete[] arrMVP;
	delete[] arrP;
	delete[] arrV;
	delete[] arrM;
	delete MVP;
	delete quadProj;
	delete quadView;
	delete quadModelView;
	delete scalarMatrix;

	//delete position;
	//delete screenSize;
	//delete screenSpacePosition;

	//delete vaoSprite;
	//delete model;
}