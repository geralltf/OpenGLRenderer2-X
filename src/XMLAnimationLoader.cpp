#include "XMLAnimationLoader.h"
#include "AnimatedModelLoader.h"
#include <iostream>

AnimationLoader::AnimationLoader(pugi::xpath_node animationData, pugi::xpath_node jointHierarchy)
{
	this->animationData = animationData;
	this->jointHierarchy = jointHierarchy;
}

AnimationData* AnimationLoader::extractAnimation() 
{
	checkNodeHierarchy();

	std::string* rootNode = findRootJointName();

	std::vector<float> times = getKeyTimes();

	float duration = times[times.size() - 1];

	std::vector<KeyFrameData*>* keyFrames = initKeyFrames(times);

	auto animationNodes = animationData.node().children("animation");
	for (pugi::xpath_node jointNode : animationNodes)
	{
		loadJointTransforms(keyFrames, jointNode, rootNode);
	}
	return new AnimationData(duration, keyFrames);
}

std::vector<float> AnimationLoader::getKeyTimes()
{
	pugi::xpath_node timeData = animationData.node().child("animation").child("source").child("float_array");
	std::vector<std::string> rawTimes = StringSplit(std::string(timeData.node().text().as_string()), " ");
	int timesCount = rawTimes.size();
	std::vector<float> times = std::vector<float>(timesCount);
	for (int i = 0; i < timesCount; i++)
	{
		times[i] = std::stof(rawTimes[i]);
	}
	return times;
}

std::vector<KeyFrameData*>* AnimationLoader::initKeyFrames(std::vector<float> times)
{
	std::vector<KeyFrameData*>* frames = new std::vector<KeyFrameData*>(times.size());
	for (int i = 0; i < frames->size(); i++) {
		frames->at(i) = new KeyFrameData(times[i]);
	}
	return frames;
}

void AnimationLoader::loadJointTransforms(std::vector<KeyFrameData*>* frames, pugi::xpath_node jointData, std::string* rootNodeId)
{
	std::string* jointNameId = getJointName(jointData);
	std::string* dataId = getDataId(jointData);

	pugi::xpath_node transformData = GetChildWithAttribute(jointData, "source", "id", *dataId);
	std::string rawData = std::string(transformData.node().child("float_array").text().as_string());

	processTransforms(jointNameId, rawData, frames, *jointNameId == *rootNodeId);
}

std::string* AnimationLoader::getDataId(pugi::xpath_node jointData)
{
	std::string animID = std::string(jointData.node().attribute("id").value());
	pugi::xpath_node sampler = jointData.node().child("sampler");
	std::string samplerID = std::string(sampler.node().attribute("id").value());
	pugi::xpath_node node = GetChildWithAttribute(sampler, "input", "semantic", "OUTPUT");
	const pugi::char_t* sourceId = node.node().attribute("source").value();
	std::string* dataId = new std::string((new std::string(sourceId))->substr(1));
	return dataId;
}

std::string* AnimationLoader::getJointName(pugi::xpath_node jointData)
{
	pugi::xpath_node channelNode = jointData.node().child("channel");
	std::string data = std::string(channelNode.node().attribute("target").value());
	std::string jointName = StringSplit(data, "/")[0];
	return new std::string(jointName);
}

void AnimationLoader::processTransforms(std::string* jointName, std::string rawData, std::vector<KeyFrameData*>* keyFrames, bool root)
{
	std::vector<std::string> data;
	
	Split(rawData, " ", data, true);

	for (int i = 0; i < keyFrames->size(); i++)
	{
		Matrix4* transform = ConvertDataToMatrix(data, i);

		// Find the transpose: Convert from a Collada row-major order to column-major order.
		transform = transform->Transpose();

		if (root)
		{
			//because up axis in Blender is different to up axis in game
			transform = Matrix4::Multiply(AnimatedModelLoader::CORRECTION, transform);
		}

		JointTransformData* jointTransformData = new JointTransformData(jointName, transform);
		keyFrames->at(i)->addJointTransform(jointTransformData);
	}
}

std::string* AnimationLoader::findRootJointName()
{
	pugi::xpath_node visualScene = jointHierarchy.node().child("visual_scene");
	auto it = visualScene.node().children("node");

	// Check for Armature Node, Node id=Armature.
	pugi::xpath_node skeleton = GetChildWithAttribute(visualScene, "node", "id", "Armature");

	// Find ID of first node
	if (skeleton.node().empty())
	{
		skeleton = visualScene.node().child("node");

		return new std::string(skeleton.node().attribute("id").value());
	}
	else 
	{
		return new std::string(skeleton.node().child("node").attribute("id").value());
	}
}

void AnimationLoader::checkNodeHierarchy() 
{
	pugi::xpath_node visualScene = jointHierarchy.node().child("visual_scene");
	auto it = visualScene.node().children("node");
	int countNodes = std::distance(it.begin(), it.end());

	if (countNodes == 0)
	{
		std::cout << "There are no nodes present under visual_scene." << std::endl;
	}
	else if (countNodes > 1)
	{
		std::cout << "There are many root nodes present under visual_scene. Consider only having one. Choosing the first node." << std::endl;
	}
}

Matrix4* AnimationLoader::ConvertDataToMatrix(std::vector<std::string> data, int matrixIndex)
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


Matrix4* AnimationLoader::ConvertDataToMatrix(std::string* data)
{
	std::vector<std::string> tokens;
	Split(*data, " ", tokens, true);
	return ConvertDataToMatrix(tokens, 0);
}