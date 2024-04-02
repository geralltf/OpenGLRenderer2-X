#ifndef INVENTORY_H
#define INVENTORY_H

#include "Sprite.h"
#include "Font.h"

enum InventorySlotType
{
	Dagger = 0x00,
	GreatSword = 0x01,
	EnchantedSword = 0x02,
	Potion = 0x03,
	Potion_Red = 0x04
};

class InventoryView {
public:
	Sprite* resumeGame;
	Sprite* inventoryUI;
	Sprite* questsUI;
	Sprite* enchantedSword;
	Sprite* dagger;
	Sprite* greatsword;
	Sprite* potion;
	Sprite* potion_red;
	Sprite* scrollbar_horiz;
	Sprite* scrollbar_horiz_sliderbar;
	Sprite* hovered_item;
	Sprite* selected_item;
	Sprite* description_onhover;
	Vector2f* slots_position;
	FontRenderer* fontRenderer;
	bool visible = false;
	bool quests_visible = false;
	bool inventory_hasopened = false;
	float dt = 0;
	float prevx;
	float prevy;
	float mdx;
	float mdy;
	float originalSliderBarPosition;
	float sliderBarPosition;
	bool beginSlider = true;
	float sliderRatio;
	float progression = 0.0f;
	bool selected = false;
	InventoryView();
	~InventoryView();

	void renderSprites(sf::RenderWindow* window);

	void renderScrollView(sf::RenderWindow* window);
};

#endif