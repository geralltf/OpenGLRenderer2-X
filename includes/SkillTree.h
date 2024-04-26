#ifndef SKILLTREE_H
#define SKILLTREE_H

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "Random.h"
#include "SkillTreeNode.h"
#include "Transform.h"

class SkillTreeNode;

// A Force-Directed Diagram Layout Algorithm
// Bradley Smith - 2010/07/01
// Modified and port to C++ with OpenGL: Gerallt Franke - 2024/04/04.

/// <summary>
/// Represents a simple diagram consisting of SkillTreeNodes and connections, implementing a 
/// force-directed algorithm for automatically arranging the SkillTreeNodes.
/// </summary>
class SkillTreeDiagram 
{
public:
	const float ATTRACTION_CONSTANT = 0.1f;		// spring constant
	const float REPULSION_CONSTANT = 10000.0f;	// charge constant

	const float DEFAULT_DAMPING = 0.5f;
	const float DEFAULT_SPRING_LENGTH = 25;
	const int DEFAULT_MAX_ITERATIONS = 500;

	Random* rnd;

	std::vector<SkillTreeNode*>* Nodes;

	Vector3f* chart_origin;

	/// <summary>
	/// Initialises a new instance of the Diagram class.
	/// </summary>
	SkillTreeDiagram();

	/// <summary>
	/// Adds the specified SkillTreeNode to this Diagram.
	/// </summary>
	/// <param name="SkillTreeNode">The SkillTreeNode to add to the diagram.</param>
	/// <returns>True if the SkillTreeNode was added, false if the SkillTreeNode is already on this Diagram.</returns>
	bool AddNode(SkillTreeNode* SkillTreeNode);

	/// <summary>
	/// Runs the force-directed layout algorithm on this Diagram, using the default parameters.
	/// </summary>
	void Arrange();

	/// <summary>
	/// Runs the force-directed layout algorithm on this Diagram, offering the option of a random or deterministic layout.
	/// </summary>
	/// <param name="deterministic">Whether to use a random or deterministic layout.</param>
	void Arrange(bool deterministic);

	/// <summary>
	/// Runs the force-directed layout algorithm on this Diagram, using the specified parameters.
	/// </summary>
	/// <param name="damping">Value between 0 and 1 that slows the motion of the SkillTreeNodes during layout.</param>
	/// <param name="springLength">Value in pixels representing the length of the imaginary springs that run along the connectors.</param>
	/// <param name="maxIterations">Maximum number of iterations before the algorithm terminates.</param>
	/// <param name="deterministic">Whether to use a random or deterministic layout.</param>
	void Arrange(float damping, float springLength, int maxIterations, bool deterministic);

	/// <summary>
	/// Runs the force-directed layout algorithm on this Diagram, using the specified parameters.
	/// </summary>
	/// <param name="damping">Value between 0 and 1 that slows the motion of the SkillTreeNodes during layout.</param>
	/// <param name="springLength">Value in pixels representing the length of the imaginary springs that run along the connectors.</param>
	/// <param name="maxIterations">Maximum number of iterations before the algorithm terminates.</param>
	/// <param name="deterministic">Whether to use a random or deterministic layout.</param>
	void Arrange(float damping, float springLength, int maxIterations, bool deterministic, SkillTreeNode* parent, int depth);

	/// <summary>
	/// Calculates the attraction force between two connected SkillTreeNodes, using the specified spring length.
	/// </summary>
	/// <param name="x">The SkillTreeNode that the force is acting on.</param>
	/// <param name="y">The SkillTreeNode creating the force.</param>
	/// <param name="springLength">The length of the spring, in pixels.</param>
	/// <returns>A Vector representing the attraction force.</returns>
	Vector3f* CalcAttractionForce(SkillTreeNode* x, SkillTreeNode* y, float springLength, int ch);

	/// <summary>
	/// Calculates the distance between two points.
	/// </summary>
	/// <param name="a">The first point.</param>
	/// <param name="b">The second point.</param>
	/// <returns>The pixel distance between the two points.</returns>
	static float CalcDistance(Vector3f* a, Vector3f* b);

	/// <summary>
	/// Calculates the repulsion force between any two SkillTreeNodes in the diagram space.
	/// </summary>
	/// <param name="x">The SkillTreeNode that the force is acting on.</param>
	/// <param name="y">The SkillTreeNode creating the force.</param>
	/// <returns>A Vector representing the repulsion force.</returns>
	Vector3f* CalcRepulsionForce(SkillTreeNode* x, SkillTreeNode* y);

	/// <summary>
	/// Removes all SkillTreeNodes and connections from the diagram.
	/// </summary>
	void Clear();

	/// <summary>
	/// Determines whether the diagram contains the specified SkillTreeNode.
	/// </summary>
	/// <param name="SkillTreeNode">The SkillTreeNode to test.</param>
	/// <returns>True if the diagram contains the SkillTreeNode.</returns>
	bool ContainsNode(SkillTreeNode* SkillTreeNode);

	/// <summary>
	/// Draws the diagram using OpenGL, centering and scaling within the specified bounds.
	/// </summary>
	/// <param name="bounds">Bounds in which to draw the diagram.</param>
	void Draw(sf::RenderWindow* render_window, Transform* cameraTransform, Matrix4* projectionMatrix, Matrix4* modelview, AABB* bounds);

	/// <summary>
	/// Draws the diagram using OpenGL, centering and scaling within the specified bounds.
	/// </summary>
	/// <param name="bounds">Bounds in which to draw the diagram.</param>
	void DrawNode(sf::RenderWindow* render_window, Transform* cameraTransform, Matrix4* projectionMatrix, Matrix4* modelview, SkillTreeNode* node, AABB* bounds, Vector3f* center, float scale);

	/// <summary>
	/// Calculates the bearing angle from one point to another.
	/// </summary>
	/// <param name="start">The SkillTreeNode that the angle is measured from.</param>
	/// <param name="end">The SkillTreeNode that creates the angle.</param>
	/// <returns>The bearing angle, in degrees.</returns>
	float GetBearingAngle(Vector3f* start, Vector3f* end);

	/// <summary>
	/// Determines the logical bounds of the diagram. This is used to center and scale the diagram when drawing.
	/// </summary>
	/// <returns>A System.Drawing.Rectangle that fits exactly around every SkillTreeNode in the diagram.</returns>
	AABB* GetDiagramBounds();

	/// <summary>
	/// Removes the specified SkillTreeNode from the diagram. Any connected SkillTreeNodes will remain on the diagram.
	/// </summary>
	/// <param name="SkillTreeNode">The SkillTreeNode to remove from the diagram.</param>
	/// <returns>True if the SkillTreeNode belonged to the diagram.</returns>
	bool RemoveNode(SkillTreeNode* SkillTreeNode);

	/// <summary>
	/// Applies a scaling factor to the specified point, used for zooming.
	/// </summary>
	/// <param name="point">The coordinates to scale.</param>
	/// <param name="scale">The scaling factor.</param>
	/// <returns>A System.Drawing.Point representing the scaled coordinates.</returns>
	Vector3f* ScalePoint(Vector3f* point, float scale);
};


/// <summary>
/// Private inner class used to track the SkillTreeNode's position and velocity during simulation.
/// </summary>
class SkillTreeNodeLayoutInfo {
public:
	SkillTreeNode* node;			// reference to the SkillTreeNode in the simulation
	Vector3f* velocity;		// the SkillTreeNode's current velocity, expressed in vector form
	Vector3f* next_position;	// the SkillTreeNode's position after the next iteration

	SkillTreeNodeLayoutInfo();
	/// <summary>
	/// Initialises a new instance of the Diagram.SkillTreeNodeLayoutInfo class, using the specified parameters.
	/// </summary>
	/// <param name="SkillTreeNode"></param>
	/// <param name="velocity"></param>
	/// <param name="nextPosition"></param>
	SkillTreeNodeLayoutInfo(SkillTreeNode* _node, Vector3f* velocity, Vector3f* nextPosition);
};
#endif