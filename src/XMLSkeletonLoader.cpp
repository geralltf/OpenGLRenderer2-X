#include "XMLSkeletonLoader.h"
#include "AnimatedModelLoader.h"

SkeletonLoader::SkeletonLoader(pugi::xpath_node jointHierarchy, std::vector<std::string*>* boneOrder, std::vector<Matrix4*>* bindPoses)
{
	this->boneOrder = boneOrder;
	this->bindPoses = bindPoses;

	pugi::xpath_node visualScene = jointHierarchy.node().child("visual_scene");

	// Check for Armature Node, Node id=Armature.
	pugi::xpath_node skeleton = GetChildWithAttribute(visualScene, "node", "id", "Armature");

	if (skeleton.node().empty())
	{
		// Just find the first node (hopefully it is the root node).
		this->armatureData = visualScene.node().child("node");
	}
	else 
	{
		// We have the Armature as the root node.
		this->armatureData = skeleton;
	}
}

SkeletonData* SkeletonLoader::extractBoneData(bool& loaded)
{
	JointData* headJoint = nullptr;
	pugi::xpath_node headNode = armatureData.node().child("node");

	if (!headNode.node().empty()) 
	{
		headJoint = loadJointData(headNode, true);

		loaded = true;
	}
	
	return new SkeletonData(jointCount, headJoint);
}

JointData* SkeletonLoader::loadJointData(pugi::xpath_node jointNode, bool isRoot)
{
	JointData* joint = extractMainJointData(jointNode, isRoot);

	for (pugi::xpath_node childNode : jointNode.node().children("node"))
	{
		joint->addChild(loadJointData(childNode, false));
	}

	return joint;
}

Matrix4* SkeletonLoader::ConvertDataToMatrix(std::vector<std::string> data, int matrixIndex)
{
	Matrix4* m = Matrix4::Identity();

	int stride = 16 * matrixIndex;

	m->m00 = std::stof(data[stride + 0]);
	m->m01 = std::stof(data[stride + 1]);
	m->m02 = std::stof(data[stride + 2]);
	m->m03 = std::stof(data[stride + 3]);

	m->m10 = std::stof(data[stride + 4]);
	m->m11 = std::stof(data[stride + 5]);
	m->m12 = std::stof(data[stride + 6]);
	m->m13 = std::stof(data[stride + 7]);

	m->m20 = std::stof(data[stride + 8]);
	m->m21 = std::stof(data[stride + 9]);
	m->m22 = std::stof(data[stride + 10]);
	m->m23 = std::stof(data[stride + 11]);

	m->m30 = std::stof(data[stride + 12]);
	m->m31 = std::stof(data[stride + 13]);
	m->m32 = std::stof(data[stride + 14]);
	m->m33 = std::stof(data[stride + 15]);

	return m;
}


Matrix4* SkeletonLoader::ConvertDataToMatrix(std::string* data)
{
	std::vector<std::string> tokens;
	Split(*data, " ", tokens, true);
	return ConvertDataToMatrix(tokens, 0);
}

JointData* SkeletonLoader::extractMainJointData(pugi::xpath_node jointNode, bool isRoot)
{
	std::string* sid = new std::string(jointNode.node().attribute("sid").value());
	std::string* name = new std::string(jointNode.node().attribute("name").value());
	std::string* id = new std::string(jointNode.node().attribute("id").value()); 
	// blender changes the id but it is best to stick with the id attribute

	int index = -1;
	auto it = std::find(boneOrder->begin(), boneOrder->end(), id);
	if (it != boneOrder->end())
	{
		index = std::distance(boneOrder->begin(), it);
	}

	std::string* matrixData = new std::string(jointNode.node().child("matrix").text().as_string());
	Matrix4* localBindTransform; 

	localBindTransform = ConvertDataToMatrix(matrixData);

	// Find the transpose: Convert from a Collada row-major order to column-major order.
	localBindTransform = localBindTransform->Transpose();
	
	if (isRoot)
	{
		//because in Blender z is up, but in our game y is up.
		localBindTransform = Matrix4::Multiply(AnimatedModelLoader::CORRECTION, localBindTransform);
	}

	Matrix4* inverseBindPoseTransform = (*bindPoses)[index];

	jointCount++;
	return new JointData(index, id, name, sid, localBindTransform, inverseBindPoseTransform);
}