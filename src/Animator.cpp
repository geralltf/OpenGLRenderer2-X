#include "Animator.h"
#include "TimeManager.h"
#include <stack>
#include <queue>

void Animator::doAnimation(Animation* animation)
{
	this->animationTime = 0;
	this->currentAnimation = animation;
}

std::map<std::string*, Matrix4*>* Animator::GetDefaultPose()
{
	std::map<std::string*, Matrix4*>* currentPose = new std::map<std::string*, Matrix4*>();

	std::vector<KeyFrame*>* allFrames = currentAnimation->getKeyFrames();
	
	KeyFrame* firstFrame = allFrames->at(0);

	std::map<std::string*, JointTransform*>* keyframeJointMap = firstFrame->getJointKeyFrames();

	for (auto const& keysmap : *keyframeJointMap)
	{
		std::string* jointName = keysmap.first;
		JointTransform* currentTransform = keysmap.second;
		Matrix4* localTransform = currentTransform->getLocalTransform();

		currentPose->insert(std::pair<std::string*, Matrix4*>(jointName, localTransform));
	}

	return currentPose;
}

void Animator::update()
{
	if (currentAnimation != nullptr)
	{
		if (currentAnimation->getKeyFrames()->size() > 0)
		{
			increaseAnimationTime();

			std::map<std::string*, Matrix4*>* currentPose = nullptr;

			//currentPose = GetDefaultPose();
			currentPose = calculateCurrentAnimationPose();

			Joint* root = entity->getRootJoint();

			if (root != nullptr)
			{
				Matrix4* currentTransform = Matrix4::Identity();

				applyPoseToJoints(currentPose, root, &currentTransform);
			}
		}
	}
}

void Animator::increaseAnimationTime()
{
	animationTime += TimeManager::GetFrameTime();

	if (animationTime > currentAnimation->getLength()) 
	{
		animationTime = std::fmod(animationTime, currentAnimation->getLength());
	}
}

std::map<std::string*, Matrix4*>* Animator::calculateCurrentAnimationPose()
{
	std::vector<KeyFrame*>* frames = getPreviousAndNextFrames();

	float progression = calculateProgression(frames->at(0), frames->at(1));

	if (tracing)
	{
		std::cout << "progression: " << progression << std::endl;
	}

	return interpolatePoses(frames->at(0), frames->at(1), progression);
}

void Animator::applyPoseToJoints(std::map<std::string*, Matrix4*>* currentPose, Joint* rootJoint, Matrix4** parentTransform)
{
	Matrix4* currentLocalTransform = Matrix4::Identity();
	bool first = false;
	bool second = false;

	for (auto i = currentPose->begin(); i != currentPose->end(); i++)
	{
		if (*i->first == *rootJoint->id)
		{
			first = true;
			currentLocalTransform = i->second;
			break;
		}

	}
	if (!first)
	{
		for (auto i = currentPose->begin(); i != currentPose->end(); i++)
		{
			if (*i->first == *rootJoint->name)
			{
				second = true;
				currentLocalTransform = i->second;
				break;
			}
		}
	}

	if (!first && !second)
	{
		// There was no keyframe pose made so this model doesn't move from its bind pose.
		currentLocalTransform = rootJoint->getLocalBindTransform(); // Keeps the model in the bind pose
	}

	Matrix4* currentTransform = Matrix4::Multiply(*parentTransform, currentLocalTransform);

	for (Joint* childJoint : *rootJoint->children)
	{
		childJoint->depth = rootJoint->depth + 1;

		if (tracing)
		{
			for (int i = 0; i < childJoint->depth; i++)
			{
				std::cout << "___";
			}
			std::cout << childJoint->index << " id: " << *childJoint->id << " name: " << *childJoint->name << std::endl;
		}

		applyPoseToJoints(currentPose, childJoint, &currentTransform);
	}

	currentTransform = Matrix4::Multiply(currentTransform, rootJoint->getInverseBindTransform());
	rootJoint->setAnimationTransform(currentTransform);
}

std::vector<KeyFrame*>* Animator::getPreviousAndNextFrames()
{
	std::vector<KeyFrame*>* allFrames = currentAnimation->getKeyFrames();
	KeyFrame* previousFrame = allFrames->at(0);
	KeyFrame* nextFrame = allFrames->at(0);
	for (int i = 1; i < allFrames->size(); i++)
	{
		nextFrame = allFrames->at(i);
		if (nextFrame->getTimeStamp() > animationTime)
		{
			break;
		}
		previousFrame = allFrames->at(i);
	}

	std::vector<KeyFrame*>* result = new std::vector<KeyFrame*>();
	result->push_back(previousFrame);
	result->push_back(nextFrame);

	return result;
}

float Animator::calculateProgression(KeyFrame* previousFrame, KeyFrame* nextFrame)
{
	float totalTime = nextFrame->getTimeStamp() - previousFrame->getTimeStamp();
	float currentTime = animationTime - previousFrame->getTimeStamp();
	return currentTime / totalTime;
}

std::map<std::string*, Matrix4*>* Animator::interpolatePoses(KeyFrame* previousFrame, KeyFrame* nextFrame, float progression)
{
	std::map<std::string*, Matrix4*>* currentPose = new std::map<std::string*, Matrix4*>();
	std::map<std::string*, JointTransform*>* prevKeyframeMap = previousFrame->getJointKeyFrames();
	std::map<std::string*, JointTransform*>* nextKeyframeMap = nextFrame->getJointKeyFrames();

	for (auto const& keysmap : *prevKeyframeMap)
	{
		std::string* jointName = keysmap.first;
		JointTransform* previousTransform = nullptr;
		JointTransform* nextTransform = nullptr;

		previousTransform = keysmap.second;

		for (auto keysvalues2 : *nextKeyframeMap)
		{
			if ((*keysvalues2.first) == *jointName)
			{
				nextTransform = keysvalues2.second;

				JointTransform* currentTransform = JointTransform::interpolate(previousTransform, nextTransform, progression);

				currentPose->insert(std::pair<std::string*, Matrix4*>(jointName, currentTransform->getLocalTransform()));

				//std::cout << "Joint " << *jointName << std::endl;
			}
		}
	}

	return currentPose;
}