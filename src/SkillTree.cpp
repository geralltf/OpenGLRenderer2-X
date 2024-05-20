#include "SkillTree.h"

/// <summary>
/// Initialises a new instance of the Diagram class.
/// </summary>
SkillTreeDiagram::SkillTreeDiagram()
{
	Nodes = new std::vector<SkillTreeNode*>();
}

/// <summary>
/// Adds the specified Node to this Diagram.
/// </summary>
/// <param name="node">The Node to add to the diagram.</param>
/// <returns>True if the node was added, false if the node is already on this Diagram.</returns>
bool SkillTreeDiagram::AddNode(SkillTreeNode* node) {
	if (node == nullptr) std::cout << "argument node is null" << std::endl;

	Nodes->push_back(node);
	node->diagram = this;
	for (SkillTreeNode* child : *node->connections) {
		AddNode(child);
	}

	if (std::find(Nodes->begin(), Nodes->end(), node) != Nodes->end()) {
		// add node, associate with diagram, then add all connected nodes
		//Nodes->push_back(node);
		//node->diagram = this;
		//for (SkillTreeNode* child : *node->connections) {
		//	AddNode(child);
		//}
		return true;
	}
	else
	{
		return false;
	}
}

/// <summary>
/// Runs the force-directed layout algorithm on this Diagram, using the default parameters.
/// </summary>
void SkillTreeDiagram::Arrange()
{
	Arrange(DEFAULT_DAMPING, DEFAULT_SPRING_LENGTH, DEFAULT_MAX_ITERATIONS, true);
}

/// <summary>
/// Runs the force-directed layout algorithm on this Diagram, offering the option of a random or deterministic layout.
/// </summary>
/// <param name="deterministic">Whether to use a random or deterministic layout.</param>
void SkillTreeDiagram::Arrange(bool deterministic)
{
	Arrange(DEFAULT_DAMPING, DEFAULT_SPRING_LENGTH, DEFAULT_MAX_ITERATIONS, deterministic);
}

/// <summary>
/// Runs the force-directed layout algorithm on this Diagram, using the specified parameters.
/// </summary>
/// <param name="damping">Value between 0 and 1 that slows the motion of the nodes during layout.</param>
/// <param name="springLength">Value in pixels representing the length of the imaginary springs that run along the connectors.</param>
/// <param name="maxIterations">Maximum number of iterations before the algorithm terminates.</param>
/// <param name="deterministic">Whether to use a random or deterministic layout.</param>
void SkillTreeDiagram::Arrange(float damping, float springLength, int maxIterations, bool deterministic)
{
	// random starting positions can be made deterministic by seeding System.Random with a constant
	if (rnd == nullptr)
	{
		rnd = new Random();
	}
	if (deterministic)
	{
		rnd->Seed(0);
	}

	if (this->chart_origin == nullptr) {
		this->chart_origin = new Vector3f(0.0f, 0.0f, 0.0f);
	}

	// copy nodes into an array of metadata and randomise initial coordinates for each node
	std::vector<SkillTreeNodeLayoutInfo*>* layout = new std::vector<SkillTreeNodeLayoutInfo*>(Nodes->size());
	for (int i = 0; i < Nodes->size(); i++)
	{
		SkillTreeNodeLayoutInfo* layoutInfo = layout->at(i);
		layoutInfo = new SkillTreeNodeLayoutInfo(Nodes->at(i), Vector3f::ZERO, Vector3f::ZERO);
		layoutInfo->node->location = new Vector3f(rnd->RandomFloat(-500, 500), rnd->RandomFloat(-500, 500), 0.0f);
		Nodes->at(i)->location = layoutInfo->node->location;
		layout->at(i) = layoutInfo;
	}

	int stopCount = 0;
	int iterations = 0;
	int depth = 0;

	while (true)
	{
		double totalDisplacement = 0;

		for (int i = 0; i < layout->size(); i++)
		{
			SkillTreeNodeLayoutInfo* current = layout->at(i);

			// express the node's current position as a vector, relative to the origin
			float dist = CalcDistance(current->node->location, current->next_position);
			float direction_angle_radians = GetBearingAngle(current->node->location, current->next_position);
			float size_magnitude;
			float direction_angle_degrees = direction_angle_radians * (PI / 180.0f);
			Vector3f* currentPosition = new Vector3f(dist * cos(direction_angle_degrees), dist * sin(direction_angle_degrees), 0.0f);
			Vector3f* netForce = Vector3f::ZERO;

			for (SkillTreeNode* other : *current->node->connections)
			{
				if (other != current->node)
				{
					//netForce = Vector3f::Add(netForce, CalcRepulsionForce(current->node, other));
				}
			}
			int ch = 0;
			// determine attraction caused by connections
			for (SkillTreeNode* child : *current->node->connections)
			{
				ch++;

				float numNodes = current->node->connections->size();
				float angle = (ch / (numNodes / 2.0f)) * PI; // Calculate the angle at which the element will be placed.
				float radius = 50.0f;
				float width = 50.0f;

				// For a semicircle, we would use (i / numNodes) * Math.PI.
				float x = (radius * cos(angle)) + (width / 2); // Calculate the x position of the element.
				float y = (radius * sin(angle)) + (width / 2); // Calculate the y position of the element.

				current->node->location = new Vector3f(this->chart_origin->x + x, this->chart_origin->y + y, this->chart_origin->z);

				//netForce = Vector3f::Add(netForce, CalcAttractionForce(current->node, child, springLength, ch));

				Arrange(damping, springLength, maxIterations, deterministic, child, depth + 1);
			}

			// apply net force to node velocity
			current->velocity = Vector3f::Scale(Vector3f::Add(current->velocity, netForce), damping);

			// apply velocity to node position
			current->next_position = Vector3f::Add(currentPosition, current->velocity);

			//current->node->location = current->next_position;
		}

		// move nodes to resultant positions (and calculate total displacement)
		for (int i = 0; i < layout->size(); i++) {
			SkillTreeNodeLayoutInfo* current = layout->at(i);

			totalDisplacement += CalcDistance(current->node->location, current->next_position);
			
			//current->node->location = current->next_position;
		}

		iterations++;
		//if (totalDisplacement < 10) stopCount++;
		//if (stopCount > 15) break;
		if (depth > 4) break;
		if (iterations > maxIterations) break;
	}

	// center the diagram around the origin
	AABB* logicalBounds = GetDiagramBounds();
	Vector3f* size = logicalBounds->GetSize();
	Vector3f* midPoint = new Vector3f(
		logicalBounds->Center->x + (size->x / 2),
		logicalBounds->Center->y + (size->y / 2),
		0.0f);

	for (SkillTreeNode* node : *Nodes) {
		//node->location = Vector3f::Subtract(node->location, midPoint);
	}
}


/// <summary>
/// Runs the force-directed layout algorithm on this Diagram, using the specified parameters.
/// </summary>
/// <param name="damping">Value between 0 and 1 that slows the motion of the nodes during layout.</param>
/// <param name="springLength">Value in pixels representing the length of the imaginary springs that run along the connectors.</param>
/// <param name="maxIterations">Maximum number of iterations before the algorithm terminates.</param>
/// <param name="deterministic">Whether to use a random or deterministic layout.</param>
void SkillTreeDiagram::Arrange(float damping, float springLength, int maxIterations, bool deterministic, SkillTreeNode* parent, int depth)
{
	// random starting positions can be made deterministic by seeding System.Random with a constant
	if (rnd == nullptr)
	{
		rnd = new Random();
	}
	if (deterministic) 
	{
		rnd->Seed(0);
	}

	// copy nodes into an array of metadata and randomise initial coordinates for each node
	std::vector<SkillTreeNodeLayoutInfo*>* layout = new std::vector<SkillTreeNodeLayoutInfo*>(parent->connections->size());
	for (int i = 0; i < parent->connections->size(); i++)
	{
		SkillTreeNodeLayoutInfo* layoutInfo = layout->at(i);
		layoutInfo = new SkillTreeNodeLayoutInfo(parent->connections->at(i), Vector3f::ZERO, Vector3f::ZERO);
		layoutInfo->node->location = new Vector3f(rnd->RandomFloat(-50, 50), rnd->RandomFloat(-50, 50), 0.0f);
		//Nodes->at(i)->location = layoutInfo->node->location;
		layout->at(i) = layoutInfo;
	}

	int stopCount = 0;
	int iterations = 0;

	while (true) 
	{
		double totalDisplacement = 0;

		for (int i = 0; i < layout->size(); i++) 
		{
			SkillTreeNodeLayoutInfo* current = layout->at(i);

			// express the node's current position as a vector, relative to the origin
			float dist = CalcDistance(current->node->location, current->next_position);
			float direction_angle_radians = GetBearingAngle(current->node->location, current->next_position);
			float size_magnitude;
			float direction_angle_degrees = direction_angle_radians * (PI / 180.0f);
			Vector3f* currentPosition = new Vector3f(dist * cos(direction_angle_degrees), dist * sin(direction_angle_degrees), 0.0f);
			Vector3f* netForce = Vector3f::ZERO;

			
			int ch = 0;

			for (SkillTreeNode* child : *current->node->connections)
			{
				float numNodes = current->node->connections->size();
				float angle = (ch / (numNodes / 2.0f)) * PI; // Calculate the angle at which the element will be placed.
				float radius = 50.0f;
				float width = 50.0f;

				// For a semicircle, we would use (i / numNodes) * Math.PI.
				float x = (radius * cos(angle)) + (width / 2); // Calculate the x position of the element.
				float y = (radius * sin(angle)) + (width / 2); // Calculate the y position of the element.

				current->node->location = new Vector3f(this->chart_origin->x + x, this->chart_origin->y + y, this->chart_origin->z);


				// determine repulsion between nodes
				if (child != current->node)
				{
					//netForce = Vector3f::Add(netForce, CalcRepulsionForce(current->node, child));
				}

				// determine attraction caused by connections
				ch++;

				//netForce = Vector3f::Add(netForce, CalcAttractionForce(current->node, child, springLength, ch));

				//if (child->connections->size() > 0)
				//{
				//	Arrange(damping, springLength, maxIterations, deterministic, child, depth + 1);
				//}
			}

			// apply net force to node velocity
			current->velocity = Vector3f::Scale(Vector3f::Add(current->velocity, netForce), damping);
			
			// apply velocity to node position
			current->next_position = Vector3f::Add(currentPosition, current->velocity);

			//current->node->location = current->next_position;
		}

		// move nodes to resultant positions (and calculate total displacement)
		for (int i = 0; i < layout->size(); i++) {
			SkillTreeNodeLayoutInfo* current = layout->at(i);

			totalDisplacement += CalcDistance(current->node->location, current->next_position);
			//current->node->location = current->next_position;


			//Arrange(damping, springLength, maxIterations, deterministic, current->node, depth + 1);
		}

		iterations++;
		//if (totalDisplacement < 10) stopCount++;
		//if (stopCount > 15) break;
		if (depth > 4) break;
		if (iterations > maxIterations) break;
	}

	// center the diagram around the origin
	AABB* logicalBounds = GetDiagramBounds();
	Vector3f* size = logicalBounds->GetSize();
	Vector3f* midPoint = new Vector3f(
		logicalBounds->Center->x + (size->x / 2),
		logicalBounds->Center->y + (size->y / 2),
		0.0f);

	for (SkillTreeNode* node : *Nodes) {
		//node->location = Vector3f::Subtract(node->location, midPoint);
	}
}

/// <summary>
/// Calculates the attraction force between two connected nodes, using the specified spring length.
/// </summary>
/// <param name="x">The node that the force is acting on.</param>
/// <param name="y">The node creating the force.</param>
/// <param name="springLength">The length of the spring, in pixels.</param>
/// <returns>A Vector representing the attraction force.</returns>
Vector3f* SkillTreeDiagram::CalcAttractionForce(SkillTreeNode* x, SkillTreeNode* y, float springLength, int ch)
{
	float dist = CalcDistance(x->location, y->location);
	float proximity = std::max(dist, 1.0f);

	proximity = std::max(proximity - springLength, 0.0f);

	// Hooke's Law: F = -kx
	float force = ATTRACTION_CONSTANT * proximity;
	float angle_radians = GetBearingAngle(x->location, y->location);

	float angle_degrees = angle_radians * (PI / 180.0f);// *(360.0f / (((float)ch + 10) * 10));

	float size = force;

	Vector3f* attraction_force = new Vector3f(size * cos(angle_degrees), size * sin(angle_degrees), 0.0f);
	//return new Vector(force, angle);
	return attraction_force;
}

/// <summary>
/// Calculates the distance between two points.
/// </summary>
/// <param name="a">The first point.</param>
/// <param name="b">The second point.</param>
/// <returns>The pixel distance between the two points.</returns>
float SkillTreeDiagram::CalcDistance(Vector3f* a, Vector3f* b)
{
	float dist = Vector3f::DistanceSquared(a, b);
	return dist;
}

/// <summary>
/// Calculates the repulsion force between any two nodes in the diagram space.
/// </summary>
/// <param name="x">The node that the force is acting on.</param>
/// <param name="y">The node creating the force.</param>
/// <returns>A Vector representing the repulsion force.</returns>
Vector3f* SkillTreeDiagram::CalcRepulsionForce(SkillTreeNode* x, SkillTreeNode* y)
{
	float proximity = std::max(CalcDistance(x->location, y->location), 1.0f);

	// Coulomb's Law: F = k(Qq/r^2)
	float force = -(REPULSION_CONSTANT / pow(proximity, 2));
	float angle_radians = GetBearingAngle(x->location, y->location);
	float angle_degrees = angle_radians * (PI / 180.0f);
	float size_magnitude = force;
	Vector3f* repulsion_force = new Vector3f(size_magnitude * cos(angle_degrees), size_magnitude * sin(angle_degrees), 0.0f);

	//return new Vector(force, angle);

	return repulsion_force;
}

/// <summary>
/// Removes all nodes and connections from the diagram.
/// </summary>
void SkillTreeDiagram::Clear()
{
	Nodes->clear();
}

/// <summary>
/// Determines whether the diagram contains the specified node.
/// </summary>
/// <param name="node">The node to test.</param>
/// <returns>True if the diagram contains the node.</returns>
bool SkillTreeDiagram::ContainsNode(SkillTreeNode* node)
{
	if (!Nodes->empty())
	{
		if (std::find(Nodes->begin(), Nodes->end(), node) != Nodes->end())
		{
			// Nodes contains specified 'node'.
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

/// <summary>
/// Draws the diagram using OpenGL, centering and scaling within the specified bounds.
/// </summary>
/// <param name="bounds">Bounds in which to draw the diagram.</param>
void SkillTreeDiagram::Draw(sf::RenderWindow* render_window, Transform* cameraTransform, Matrix4* projectionMatrix, Matrix4* modelview, AABB* bounds)
{
	Vector3f* center = new Vector3f(
		bounds->GetCenter()->x + (bounds->GetSize()->x / 2.0f),
		bounds->GetCenter()->y + (bounds->GetSize()->y / 2.0f),
		0.0f);

	// determine the scaling factor
	AABB* logicalBounds = GetDiagramBounds();
	float scale = 1;
	if (logicalBounds->GetSize()->x > logicalBounds->GetSize()->y)
	{
		if (logicalBounds->GetSize()->x != 0)
		{
			scale = (float)std::min(bounds->GetSize()->x, bounds->GetSize()->y) / (float)logicalBounds->GetSize()->x;
		}
	}
	else
	{
		if (logicalBounds->GetSize()->x != 0)
		{
			scale = (float)std::min(bounds->GetSize()->x, bounds->GetSize()->y) / (float)logicalBounds->GetSize()->y;
		}
	}

	// draw all of the connectors first
	for (SkillTreeNode* node : *Nodes)
	{
		Vector3f* source = ScalePoint(node->location, scale);

		// connectors
		for (SkillTreeNode* other : *node->connections)
		{
			Vector3f* destination = ScalePoint(other->location, scale);
			node->DrawConnector(render_window, cameraTransform, projectionMatrix, modelview, Vector3f::Add(center, source), Vector3f::Add(center, destination), other);
		}
	}

	int ch = 0;
	// then draw all of the nodes
	for (SkillTreeNode* node : *Nodes) 
	{
		ch++;

		Vector3f* destination = ScalePoint(node->location, scale);

		node->size = new Vector3f(8, 8, 8);
		Vector3f* nodeSize = node->size;
		Vector3f* nodeBounds = new Vector3f(
			center->x + destination->x - (nodeSize->x / 2.0f),
			center->y + destination->y - (nodeSize->y / 2.0f),
			0.0f
		);
		nodeSize = nodeBounds;

		Vector3f* node_center = new Vector3f(
			center->x + destination->x - (nodeSize->x / 2.0f),
			center->y + destination->y - (nodeSize->y / 2.0f),
			0.0f
		);
		Vector3f* half_size = new Vector3f(
			nodeSize->x,
			nodeSize->y,
			0.0f
		); 

		AABB* nodeBoundsAABB = new AABB(node_center, half_size);

		float numNodes = Nodes->size();
		float angle = (ch / (numNodes / 2.0f)) * PI; // Calculate the angle at which the element will be placed.
		//float angle = (ch / numNodes) * PI;
		float radius = 5.0f;
		float width = 10.0f;

		// For a semicircle, we would use (i / numNodes) * Math.PI.
		float x = (radius * cos(angle)) + (width / 2); // Calculate the x position of the element.
		float y = (radius * sin(angle)) + (width / 2); // Calculate the y position of the element.

		node->location = new Vector3f(x, y, 0.0f);
		//node->location = node_center;

		node->DrawNode(render_window, nodeBoundsAABB);

		DrawNode(render_window, cameraTransform, projectionMatrix, modelview, node, nodeBoundsAABB, center, scale);
	}
}

/// <summary>
/// Draws the diagram using OpenGL, centering and scaling within the specified bounds.
/// </summary>
/// <param name="bounds">Bounds in which to draw the diagram.</param>
void SkillTreeDiagram::DrawNode(sf::RenderWindow* render_window, Transform* cameraTransform, Matrix4* projectionMatrix, Matrix4* modelview, SkillTreeNode* parent_node, AABB* bounds, Vector3f* center, float scale)
{
	// draw all of the connectors first
	for (SkillTreeNode* node : *parent_node->connections)
	{
		Vector3f* source = ScalePoint(node->location, scale);

		// connectors
		for (SkillTreeNode* other : *node->connections)
		{
			Vector3f* destination = ScalePoint(other->location, scale);
			node->DrawConnector(render_window, cameraTransform, projectionMatrix, modelview, Vector3f::Add(center, source), Vector3f::Add(center, destination), other);
		
			DrawNode(render_window, cameraTransform, projectionMatrix, modelview, other, bounds, center, scale);
		}
	}

	scale = scale * 2.0f;

	int ch = 0;
	// then draw all of the nodes
	for (SkillTreeNode* node : *parent_node->connections) 
	{
		ch++;

		Vector3f* destination = ScalePoint(node->location, scale);

		node->size = new Vector3f(8, 8, 8);
		Vector3f* nodeSize = node->size;
		Vector3f* nodeBounds = new Vector3f(
			center->x + destination->x - (nodeSize->x / 2.0f),
			center->y + destination->y - (nodeSize->y / 2.0f),
			0.0f
		);
		nodeSize = nodeBounds;

		Vector3f* node_center = new Vector3f(
			center->x + destination->x - (nodeSize->x / 2.0f),
			center->y + destination->y - (nodeSize->y / 2.0f),
			0.0f
		);
		Vector3f* half_size = new Vector3f(
			nodeSize->x,
			nodeSize->y,
			0.0f
		);
		AABB* nodeBoundsAABB = new AABB(node_center, half_size);

		float numNodes = parent_node->connections->size();
		float angle = (ch / (numNodes / scale)) * PI; // Calculate the angle at which the element will be placed.
		float radius = 500.0f * scale;
		float width = 10.0f;

		// For a semicircle, we would use (i / numNodes) * Math.PI.
		float x = (radius * cos(angle)) + (width / scale); // Calculate the x position of the element.
		float y = (radius * sin(angle)) + (width / scale); // Calculate the y position of the element.

		node->location = new Vector3f(x, y, 0.0f);
		//node->location = node_center;
		node->DrawNode(render_window, nodeBoundsAABB);

		DrawNode(render_window, cameraTransform, projectionMatrix, modelview, node, nodeBoundsAABB, center, scale);
	}
}

/// <summary>
/// Calculates the bearing angle from one point to another.
/// </summary>
/// <param name="start">The node that the angle is measured from.</param>
/// <param name="end">The node that creates the angle.</param>
/// <returns>The bearing angle, in degrees.</returns>
float SkillTreeDiagram::GetBearingAngle(Vector3f* start, Vector3f* end) {
	Vector3f* half = new Vector3f(start->x + ((end->x - start->x) / 2.0f), start->y + ((end->y - start->y) / 2.0f), 0.0f);

	float diffX = (float)(half->x - start->x);
	float diffY = (float)(half->y - start->y);

	if (diffX == 0) diffX = 0.001;
	if (diffY == 0) diffY = 0.001;

	float angle;
	if (abs(diffX) > abs(diffY)) {
		angle = tanh(diffY / diffX) * (180.0 / PI);
		if (((diffX < 0) && (diffY > 0)) || ((diffX < 0) && (diffY < 0))) angle += 180;
	}
	else {
		angle = tanh(diffX / diffY) * (180.0 / PI);
		if (((diffY < 0) && (diffX > 0)) || ((diffY < 0) && (diffX < 0))) angle += 180;
		angle = (180 - (angle + 90));
	}

	return angle;
}

/// <summary>
/// Determines the logical bounds of the diagram. This is used to center and scale the diagram when drawing.
/// </summary>
/// <returns>A System.Drawing.Rectangle that fits exactly around every node in the diagram.</returns>
AABB* SkillTreeDiagram::GetDiagramBounds()
{
	float minX = std::numeric_limits<float>::max();
	float minY = std::numeric_limits<float>::max();
	float minZ = std::numeric_limits<float>::max();
	float maxX = std::numeric_limits<float>::min();
	float maxY = std::numeric_limits<float>::min();
	float maxZ = std::numeric_limits<float>::min();
	for (SkillTreeNode* node : *Nodes) {
		if (node->location->x < minX) minX = node->location->x;
		if (node->location->x > maxX) maxX = node->location->x;
		if (node->location->y < minY) minY = node->location->y;
		if (node->location->y > maxY) maxY = node->location->y;
		if (node->location->z < minZ) minZ = node->location->z;
		if (node->location->z > maxZ) maxZ = node->location->z;
	}
	AABB* aabb;
	Vector3f* diagram_location = Vector3f::ZERO;
	Vector3f* diagram_half_size = new Vector3f(maxX  - minX, maxY - minY, maxZ - minZ);
	aabb = new AABB(diagram_location, diagram_half_size);
	//return Rectangle.FromLTRB(minX, minY, maxX, maxY);
	return aabb;
}

/// <summary>
/// Removes the specified node from the diagram. Any connected nodes will remain on the diagram.
/// </summary>
/// <param name="node">The node to remove from the diagram.</param>
/// <returns>True if the node belonged to the diagram.</returns>
bool SkillTreeDiagram::RemoveNode(SkillTreeNode* node)
{
	node->diagram = nullptr;
	for (SkillTreeNode* other : *Nodes)
	{
		if (!Nodes->empty() && (other != node))
		{
			std::vector<SkillTreeNode*>::iterator it = std::find(other->connections->begin(), other->connections->end(), node);

			if (it != Nodes->end())
			{
				// Nodes contains specified 'node'.
				other->Disconnect(node);
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}

	std::vector<SkillTreeNode*>::iterator it2 = std::find(Nodes->begin(), Nodes->end(), node);
	if (Nodes->erase(it2) != Nodes->end()) {
		return true;
	}
	return false;
}

/// <summary>
/// Applies a scaling factor to the specified point, used for zooming.
/// </summary>
/// <param name="point">The coordinates to scale.</param>
/// <param name="scale">The scaling factor.</param>
/// <returns>A System.Drawing.Point representing the scaled coordinates.</returns>
Vector3f* SkillTreeDiagram::ScalePoint(Vector3f* point, float scale)
{
	return new Vector3f(point->x * scale, point->y * scale, point->z * scale);
}

SkillTreeNodeLayoutInfo::SkillTreeNodeLayoutInfo() {

}
SkillTreeNodeLayoutInfo::SkillTreeNodeLayoutInfo(SkillTreeNode* _node, Vector3f* velocity, Vector3f* nextPosition)
{
	this->node = _node;
	this->velocity = velocity;
	this->next_position = nextPosition;
}