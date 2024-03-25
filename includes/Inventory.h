#ifndef INVENTORY_H
#define INVENTORY_H

#include "Sprite.h"

class InventoryView {
public:
	Sprite* resumeGame;
	Sprite* inventoryUI;
	Sprite* questsUI;
	Sprite* enchantedSword;
	Sprite* dagger;
	Sprite* greatsword;
	Sprite* scrollbar_horiz;
	Sprite* scrollbar_horiz_sliderbar;
	Sprite* hovered_item;
	Sprite* selected_item;
	Vector2f* slots_position;
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
	InventoryView()
	{
		resumeGame = Sprite::Create(
			"Assets/sprites/menu_resumegame.tga", 
			new Vector2f(256, 64), 
			new Vector3f(64.0f, 90.0f, 0.0f), 
			new Vector3f(0.2f, 0.2f, 1.0f),
			true
		);
		
		inventoryUI = Sprite::Create(
			"Assets/sprites/inventory_view.tga",
			new Vector2f(640, 480),
			new Vector3f(256.0f, 1024.0f, 0.0f),
			new Vector3f(0.7f, 0.7f, 1.0f),
			true
		);

		questsUI = Sprite::Create(
			"Assets/sprites/quest_view.tga",
			new Vector2f(640, 480),
			new Vector3f(256.0f, 800.0f, 0.0f),
			new Vector3f(0.7f, 0.7f, 1.0f),
			true
		);

		enchantedSword = Sprite::Create(
			"Assets/sprites/enchanted_item.tga",
			new Vector2f(64, 64),
			new Vector3f(256.0f, 800.0f, 0.0f),
			new Vector3f(0.06f, 0.06f, 1.0f),
			true
		);

		dagger = Sprite::Create(
			"Assets/sprites/dagger.tga",
			new Vector2f(64, 64),
			new Vector3f(256.0f, 800.0f, 0.0f),
			new Vector3f(0.06f, 0.06f, 1.0f),
			true
		);

		greatsword = Sprite::Create(
			"Assets/sprites/greatsword.tga",
			new Vector2f(64, 64),
			new Vector3f(256.0f, 800.0f, 0.0f),
			new Vector3f(0.06f, 0.06f, 1.0f),
			true
		);

		scrollbar_horiz = Sprite::Create(
			"Assets/sprites/scrollbar_horiz.tga",
			new Vector2f(246, 14),
			new Vector3f(256.0f, 800.0f, 0.0f),
			new Vector3f(0.3f, 0.3f, 1.0f),
			true
		);

		scrollbar_horiz_sliderbar = Sprite::Create(
			"Assets/sprites/scrollbar_horiz_sliderbar.tga",
			new Vector2f(11, 10),
			new Vector3f(256.0f, 800.0f, 0.0f),
			new Vector3f(0.3f, 0.3f, 1.0f),
			true
		);

		hovered_item = Sprite::Create(
			"Assets/sprites/hovered_item.tga",
			new Vector2f(64, 64),
			new Vector3f(256.0f, 800.0f, 0.0f),
			new Vector3f(0.06f, 0.06f, 1.0f),
			true
		);

		selected_item = Sprite::Create(
			"Assets/sprites/selected_item.tga",
			new Vector2f(64, 64),
			new Vector3f(256.0f, 800.0f, 0.0f),
			new Vector3f(0.06f, 0.06f, 1.0f),
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

			if (!inventory_hasopened)
			{
				Vector3f* end = new Vector3f(128.0f, 720.0f, 0.0f);
				Vector3f* start = new Vector3f(128.0f, -1024.0f, 0.0f);
				float progressionRatio = 0.125f;
				dt += progressionRatio;
				inventoryUI->position = Vector3f::Lerp(start, end, dt);
				if (dt >= 1.0f) 
				{
					inventory_hasopened = true;
					dt = 0.0f;
				}
			}

			resumeGame->render(window);
			inventoryUI->render(window);

			if (inventory_hasopened)
			{
				renderScrollView(window);
			}
		}
		else 
		{
			inventory_hasopened = false;
		}

		if (quests_visible)
		{
			questsUI->render(window);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
		{
			visible = !visible;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
		{
			quests_visible = !quests_visible;
		}
	}

	enum InventorySlotType
	{
		Dagger = 0x00,
		GreatSword = 0x01,
		EnchantedSword = 0x02
	};
	void renderScrollView(sf::RenderWindow* window)
	{
		slots_position = new Vector2f(60.0f, 44.0f);

		float startX = 148.0f + (5 * 64) + 16;
		float startY = 148.0f;
		int maximumViewItemsCount = 20;
		int w = ((1.0f - sliderRatio) * maximumViewItemsCount);
		int h = ((1.0f - 0.0f) * maximumViewItemsCount);
		Vector2f* beginValue = new Vector2f();

		std::vector<InventorySlotType>* inventory_slots = new std::vector<InventorySlotType>();

		inventory_slots->push_back(InventorySlotType::EnchantedSword);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::GreatSword);
		inventory_slots->push_back(InventorySlotType::EnchantedSword);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::GreatSword);
		inventory_slots->push_back(InventorySlotType::EnchantedSword);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::GreatSword);
		inventory_slots->push_back(InventorySlotType::EnchantedSword);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::GreatSword);
		inventory_slots->push_back(InventorySlotType::EnchantedSword);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::GreatSword);
		inventory_slots->push_back(InventorySlotType::EnchantedSword);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::GreatSword);
		inventory_slots->push_back(InventorySlotType::EnchantedSword);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::GreatSword);
		inventory_slots->push_back(InventorySlotType::EnchantedSword);
		inventory_slots->push_back(InventorySlotType::GreatSword);
		inventory_slots->push_back(InventorySlotType::GreatSword);
		inventory_slots->push_back(InventorySlotType::GreatSword);
		inventory_slots->push_back(InventorySlotType::GreatSword);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::EnchantedSword);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);		
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::EnchantedSword);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);		
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::EnchantedSword);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);		
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::EnchantedSword);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);		
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::EnchantedSword);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);		
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::EnchantedSword);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);		
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::EnchantedSword);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::Dagger);
		inventory_slots->push_back(InventorySlotType::EnchantedSword);
		inventory_slots->push_back(InventorySlotType::EnchantedSword);
		inventory_slots->push_back(InventorySlotType::EnchantedSword);
		std::vector<bool>* inventory_slots_equipped = new std::vector<bool>(inventory_slots->size());
		int width = 5;
		int xx = 0;
		int yy = 0;
		int page_count = 5 * 13;
		int master_index = 0;
		for (int index = 0; index < inventory_slots->size(); index++)
		{
			InventorySlotType slotType = inventory_slots->at((master_index + index) % inventory_slots->size());

			xx = (index) % width;
			yy = (index) / width;

			bool can_render = true;
			if (yy >= 13) {
				can_render = false;				
			}

			int num_pages_count = (int)(((float)inventory_slots->size() / (float)page_count));

			master_index = ((num_pages_count * page_count) * sliderRatio);

			if (can_render)
			{
				switch (slotType)
				{
				case InventorySlotType::Dagger:
					dagger->position = new Vector3f(startX + (xx * slots_position->x), startY + (yy * slots_position->y), 0.0f);
					dagger->scale = new Vector3f(0.03f, 0.05f, 1.0f);
					dagger->render(window);
					break;
				case InventorySlotType::GreatSword:
					greatsword->position = new Vector3f(startX + (xx * slots_position->x), startY + (yy * slots_position->y), 0.0f);
					greatsword->scale = new Vector3f(0.03f, 0.05f, 1.0f);
					greatsword->render(window);
					break;
				case InventorySlotType::EnchantedSword:
					enchantedSword->position = new Vector3f(startX + (xx * slots_position->x), startY + (yy * slots_position->y), 0.0f);
					enchantedSword->scale = new Vector3f(0.03f, 0.05f, 1.0f);
					enchantedSword->render(window);
					break;
				}

				bool hovered = false;

				if (inventory_slots_equipped->size() - 1 >= index)
				{
					inventory_slots_equipped->at(index) = false;
				}
				inventory_slots_equipped->at(index) = false;
				selected = false;

				if (sf::Mouse::getPosition().x >= startX + (xx * slots_position->x) && sf::Mouse::getPosition().x <= startX + (xx * slots_position->x) + 64.0f)
				{
					if (sf::Mouse::getPosition().y >= startY + (yy * slots_position->y) && sf::Mouse::getPosition().y <= startY + (yy * slots_position->y) + 64.0f)
					{
						hovered = true;

						if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
						{
							inventory_slots_equipped->at(index) = true;
							selected = true;
						}
					}
				}

				if (hovered)
				{
					hovered_item->position = new Vector3f(startX + (xx * slots_position->x), startY + (yy * slots_position->y), 0.0f);
					hovered_item->scale = new Vector3f(0.03f, 0.05f, 1.0f);
					hovered_item->render(window);
				}

				if (selected)
				{
					selected_item->position = new Vector3f(startX + (xx * slots_position->x), startY + (yy * slots_position->y), 0.0f);
					selected_item->scale = new Vector3f(0.03f, 0.05f, 1.0f);
					selected_item->render(window);
				}
			}
		}
		progression += 0.01f;

		if (beginSlider)
		{
			sliderBarPosition = startX + 16.0f;
			originalSliderBarPosition = sliderBarPosition;
			beginSlider = false;
		}
		mdx = prevx - sf::Mouse::getPosition().x;
		mdy = prevy - sf::Mouse::getPosition().y;
		prevx = sf::Mouse::getPosition().x;
		prevy = sf::Mouse::getPosition().y;


		scrollbar_horiz->position = new Vector3f(startX, startY + 560.0f, 0.0f);
		scrollbar_horiz->scale = new Vector3f(0.160f, 0.02f, 1.0f);
		scrollbar_horiz->render(window);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			sliderBarPosition += -mdx * 0.1f;

			if (sliderBarPosition >= 747.0f)
			{
				sliderBarPosition = 747.0f;
			}
			if (sliderBarPosition <= originalSliderBarPosition)
			{
				sliderBarPosition = originalSliderBarPosition;
			}

			sliderRatio = (747.0f - sliderBarPosition) / (747.0f - originalSliderBarPosition);

		}
		scrollbar_horiz_sliderbar->position = new Vector3f(sliderBarPosition, startY + 560.0f - 2.0f, 0.0f);
		scrollbar_horiz_sliderbar->scale = new Vector3f(0.0125f, 0.0125f, 1.0f);
		scrollbar_horiz_sliderbar->render(window);
	}
};

#endif