#include "VertexSkinData.h"

void VertexSkinData::addJointEffect(int jointId, float weight)
{
	for (int i = 0; i < weights->size(); i++)
	{
		if (weight > (weights->at(i)))
		{
			jointIds->at(i) = jointId;
			weights->at(i) = weight;

			//std::vector<int>::iterator itJoint = jointIds.begin() + i;
			//std::vector<float>::iterator itWeight = weights.begin() + i;
			//jointIds.insert(itJoint, jointId);
			//weights.insert(itWeight, weight);
			return;
		}
	}
	jointIds->push_back(jointId);
	weights->push_back(weight);
}

void VertexSkinData::limitJointNumber(int max)
{
	if (jointIds->size() > max)
	{
		std::vector<float>* topWeights = new std::vector<float>(max);
		float total = saveTopWeights(&topWeights);
		refillWeightList(&topWeights, total);
		removeExcessJointIds(max);
	}
	else if (jointIds->size() < max)
	{
		fillEmptyWeights(max);
	}
}

void VertexSkinData::fillEmptyWeights(int max)
{
	int joint_id = 0;
	float zero_weight = 0.0f;
	while (jointIds->size() < max)
	{
		jointIds->push_back(joint_id);
		weights->push_back(zero_weight);
	}
}

float VertexSkinData::saveTopWeights(std::vector<float>** topWeightsArray)
{
	float total = 0.0f;
	float curr_w = 0.0f;
	float local_w = 0.0f;

	std::vector<float>* LIST = *topWeightsArray;
	
	auto start = LIST->begin();
	auto end = LIST->end();

	int i = 0;
	for (int element_position = 0; element_position < LIST->size() && i < weights->size(); element_position++)
	{
		local_w = weights->at(i);
		(*topWeightsArray)->insert(LIST->begin() + element_position, local_w);
		total += local_w;
		i++;
	}
	return total;
}

void VertexSkinData::refillWeightList(std::vector<float>** topWeights, float total)
{
	weights->clear();
	for (int i = 0; i < (*topWeights)->size(); i++)
	{
		float w = std::min(((**(topWeights))[i]) / total, 1.0f);
		weights->push_back(w);
	}
}

void VertexSkinData::removeExcessJointIds(int max)
{
	while (jointIds->size() > max)
	{
		//jointIds.erase(jointIds.begin() + jointIds.size() - 1);
		jointIds->erase(jointIds->end() - 1);
	}
}