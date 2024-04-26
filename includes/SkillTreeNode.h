#ifndef SKILLTREENODE_H
#define SKILLTREENODE_H

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Vector3f.h"
#include "AABB.h"
#include "SkillTree.h"
#include "Sprite.h"
#include "Inventory.h"
#include "Transform.h"

class SkillTreeDiagram;
class InventoryView;

// A Force-Directed Diagram Layout Algorithm
// Bradley Smith - 2010/07/01
//Modified and port to C++ with OpenGL: Gerallt Franke - 2024/04/04.

/// <summary>
/// Represents a node that can be added to a diagram and connected to other nodes. 
/// Provides logic for drawing itself and its connections to other nodes.
/// </summary>
class SkillTreeNode
{
public:
	SkillTreeDiagram* diagram;					// the parent diagram
	Vector3f* location;					// node position, relative to the origin
	std::vector<SkillTreeNode*>* connections;	// list of references to connected nodes (children)
	SkillTreeNode* parent;						// the parent of the current node.
	Vector3f* size;						// Gets the size of the node(for drawing purposes).
	InventoryView* inventory_view;		// underlying inventory view UI that's main job is for UI renderering.

	/// <summary>
	/// Initialises a new instance of the Node class.
	/// </summary>
	SkillTreeNode();

	/// <summary>
	/// Connects the specified child node to this node.
	/// </summary>
	/// <param name="child">The child node to add.</param>
	/// <returns>True if the node was connected to this node.</returns>
	bool AddChild(SkillTreeNode* child);

	/// <summary>
	/// Connects this node to the specified parent node.
	/// </summary>
	/// <param name="parent">The node to connect to this node.</param>
	/// <returns>True if the other node was connected to this node.</returns>
	bool AddParent(SkillTreeNode* parent);

	/// <summary>
	/// Removes any connection between this node and the specified node.
	/// </summary>
	/// <param name="other">The other node whose connection is to be removed.</param>
	/// <returns>True if a connection existed.</returns>
	bool Disconnect(SkillTreeNode* other);

	/// <summary>
	/// Draws a connector between this node and the specified child node using OpenGL. 
	/// The source and destination coordinates (relative to the Graphics surface) are also specified.
	/// </summary>
	/// <param name="from">Source coodinate.</param>
	/// <param name="to">Destination coordinate.</param>
	/// <param name="other">The other node.</param>
	void DrawConnector(sf::RenderWindow* render_window, Transform* cameraTransform, Matrix4* projectionMatrix, Matrix4* modelview, Vector3f* from, Vector3f* to, SkillTreeNode* other);

	/// <summary>
	/// Draws the node using OpenGL, within the specified bounds.
	/// </summary>
	/// <param name="bounds">The bounds in which to draw the node.</param>
	void DrawNode(sf::RenderWindow* render_window, AABB* bounds);
};

#endif