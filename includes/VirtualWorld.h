#ifndef VIRTUAL_WORLD_H
#define VIRTUAL_WORLD_H

#include <SFML/Graphics.hpp>

#include "Transform.h"
#include "Matrix4.h"
#include "Vector3f.h"
#include "Character.h"
#include "AnimatedModel.h"
#include "AnimatedModelRenderer.h"
#include "AnimatedModelLoader.h"
#include "Skybox.h"
#include "Terrain.h"
#include "OctreeRenderer.h"
#include "Random.h"
#include "Inventory.h"

class VirtualWorld 
{
public:
	Character* floor;
	Character* cactus;
	Character* character00;
	Character* character01;
	Character* character02;
	AnimatedModel* animModel;
	Texture* animDiffuseTexture;
	Texture* animNormalTexture;
	Texture* animSpecularTexture;
	Texture* animGlowTexture;
	Texture* lutTexture00;
	Texture* lutTexture01;
	Texture* lutTexture02;
	Texture* lutTexture03;
	Texture* lutTexture04;
	Animation* selectedAnimation;
	Animator* animator;
	AnimatedModelRenderer* animRenderer;
	Skybox* skybox;
	Terrain* terrain;
	OctreeRenderer* octreeRenderer;
	Random* random;
	Vector3f* worldPosition = new Vector3f(0.0f, 0.0f, 0.0f);
	InventoryView* inventoryView;
public:
	VirtualWorld();
	~VirtualWorld();
	void Initilise();
	void Render(sf::RenderWindow* window, Transform* cameraTransform, Matrix4* projectionMatrix, Matrix4* modelview, Vector3f* light_dir, Matrix4* lightModelView);
};

#endif