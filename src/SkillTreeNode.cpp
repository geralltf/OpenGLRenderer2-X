#include "SkillTreeNode.h"

/// <summary>
/// Initialises a new instance of the Node class.
/// </summary>
SkillTreeNode::SkillTreeNode() {
	location = Vector3f::ZERO;
	diagram = nullptr;
	connections = new std::vector<SkillTreeNode*>();
}

/// <summary>
/// Connects the specified child node to this node.
/// </summary>
/// <param name="child">The child node to add.</param>
/// <returns>True if the node was connected to this node.</returns>
bool SkillTreeNode::AddChild(SkillTreeNode* child) {
	if (child == nullptr) std::cout << "argument node is null" << std::endl;
	if (child != this)
	{ //&& !this.mConnections.Contains(child)) {
		child->diagram = this->diagram;
		this->connections->push_back(child);
		return true;
	}
	return false;
}

/// <summary>
/// Connects this node to the specified parent node.
/// </summary>
/// <param name="parent">The node to connect to this node.</param>
/// <returns>True if the other node was connected to this node.</returns>
bool SkillTreeNode::AddParent(SkillTreeNode* parent) {
	if (parent == nullptr) std::cout << "argument node is null" << std::endl;
	return parent->AddChild(this);
	this->parent = parent;
}

/// <summary>
/// Removes any connection between this node and the specified node.
/// </summary>
/// <param name="other">The other node whose connection is to be removed.</param>
/// <returns>True if a connection existed.</returns>
bool SkillTreeNode::Disconnect(SkillTreeNode* other)
{
	bool a = false;
	bool b = false;
	std::vector<SkillTreeNode*>::iterator it = std::find(this->connections->begin(), this->connections->end(), other);
	if (it != this->connections->end())
	{
		this->connections->erase(it);
		a = true;
	}

	std::vector<SkillTreeNode*>::iterator it2 = std::find(other->connections->begin(), other->connections->end(), other);
	if (it2 != other->connections->end())
	{
		other->connections->erase(it2);
		b = true;
	}
	return a || b;
}

/// <summary>
/// Draws a connector between this node and the specified child node using OpenGL 
/// The source and destination coordinates (relative to the Graphics surface) are also specified.
/// </summary>
/// <param name="from">Source coodinate.</param>
/// <param name="to">Destination coordinate.</param>
/// <param name="other">The other node.</param>
void SkillTreeNode::DrawConnector(sf::RenderWindow* render_window, Transform* cameraTransform, Matrix4* projectionMatrix, Matrix4* modelview, Vector3f* from, Vector3f* to, SkillTreeNode* other) {
	//graphics.DrawLine(Pens.Gray, from, to);
	inventory_view->render_skilltree_node_connection(render_window, cameraTransform, projectionMatrix, modelview, other, from, to);
}

/// <summary>
/// Draws the node using OpenGL, within the specified bounds.
/// </summary>
/// <param name="bounds">The bounds in which to draw the node.</param>
void SkillTreeNode::DrawNode(sf::RenderWindow* render_window, AABB* bounds) {
	//graphics.FillEllipse(mFill, bounds);
	//graphics.DrawEllipse(mStroke, bounds);
	inventory_view->render_skilltree_node(render_window, this, bounds);
}