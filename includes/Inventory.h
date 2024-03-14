#ifndef INVENTORY_H
#define INVENTORY_H

#include "Sprite.h"

class InventoryView {
public:
	Sprite* resumeGame;
	Sprite* inventoryUI;
	bool visible = false;

	InventoryView()
	{
		resumeGame = Sprite::Create(
			"Assets/sprites/menu_resumegame.tga", 
			new Vector2f(256, 64), 
			new Vector3f(64.0f, 90.0f, 0.0f), 
			new Vector2f(0.2f, 0.2f), 
			true
		);
		
		inventoryUI = Sprite::Create(
			"Assets/sprites/inventory_view.tga",
			new Vector2f(640, 480),
			new Vector3f(256.0f, 1024.0f, 0.0f),
			new Vector2f(0.7f, 0.7f),
			true
		);
	}
	~InventoryView()
	{
		delete resumeGame;
	}

	void renderSprites(sf::RenderWindow* window) 
	{
		if (visible)
		{
			resumeGame->render(window);
			inventoryUI->render(window);
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
		{
			visible = !visible;
		}
	}
};

#endif