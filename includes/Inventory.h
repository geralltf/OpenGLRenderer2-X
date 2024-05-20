#ifndef INVENTORY_H
#define INVENTORY_H

#include <queue>

#include "Sprite.h"
#include "Font.h"
#include "SkillTree.h"
#include "Random.h"
#include "Transform.h"

class SkillTreeNode;
class SkillTreeDiagram;

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
	SkillTreeDiagram* skillTreeDiagram;
	SkillTreeNode* node_root;
	ColourRGBA* line_colour;
	Sprite* skilltree_node;
	Sprite* skilltree_node_selected;

	Random* rng;

	bool visible = false;
	bool quests_visible = false;
	bool inventory_hasopened = false;
	bool skilltree_hasopened = false;
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
	float chart_origin_x = 0.0f;
	float chart_origin_y = 0.0f;
	float chart_origin_scale = 0.1f;

	InventoryView();
	~InventoryView();

	void create_skilltree();
	void create_skilltree_node(SkillTreeNode* parent_node, int depth);
	void render_skilltree(sf::RenderWindow* window, Transform* cameraTransform, Matrix4* projectionMatrix, Matrix4* modelview);
	void render_skilltree_node_connection(sf::RenderWindow* window, Transform* cameraTransform, Matrix4* projectionMatrix, Matrix4* modelview, SkillTreeNode* node, Vector3f* start, Vector3f* end);
	void render_skilltree_node(sf::RenderWindow* window, SkillTreeNode* node, AABB* bounds);

	void renderSprites(sf::RenderWindow* window, Transform* cameraTransform, Matrix4* projectionMatrix, Matrix4* modelview);

	void renderScrollView(sf::RenderWindow* window);
};

#endif