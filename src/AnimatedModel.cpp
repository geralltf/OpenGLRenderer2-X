#include "AnimatedModel.h"
#include <stack>

AnimatedModel::AnimatedModel(Vao* model, Joint* rootJoint, int jointCount, AnimatedModelData* entityData, Animation* animation)
{
	this->model = model;
	this->rootJoint = rootJoint;
	this->jointCount = jointCount;
	this->entityData = entityData;
	this->texture = nullptr;
	this->animation = animation;

	// Compute inverse bind poses (do this if they are not already pre-loaded)
	if(rootJoint != nullptr)
	{
		rootJoint->calcInverseBindTransform(Matrix4::Identity());
	}
}

AnimatedModel::~AnimatedModel()
{
	delete model;

	if (this->animation != nullptr)
	{
		delete animation;
	}

	delete this->entityData;
	delete this->rootJoint;
}

Vao* AnimatedModel::getModel()
{
	return model;
}

Joint* AnimatedModel::getRootJoint()
{
	return rootJoint;
}

Animation* AnimatedModel::getAnimation()
{
	return animation;
}

std::vector<Matrix4*>* AnimatedModel::getJointTransforms()
{
	std::stack<Joint*>* stack = new std::stack<Joint*>();
	std::vector<Matrix4*>* jointMatrices = new std::vector<Matrix4*>(jointCount);

	if (jointCount > 0)
	{
		stack->push(rootJoint);

		while (!stack->empty())
		{
			Joint* jointNode = stack->top();
			stack->pop();

			Matrix4* m = jointNode->getAnimatedTransform();

			if (jointMatrices->at(jointNode->index) == nullptr) 
			{
				jointMatrices->at(jointNode->index) = m;
			}

			for (Joint* childJoint : *jointNode->children)
			{
				stack->push(childJoint);
			}
		}
	}
	delete stack;
	return jointMatrices;
}