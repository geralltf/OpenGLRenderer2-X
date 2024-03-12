#include "AnimatedModelRenderer.h"

AnimatedModelRenderer::AnimatedModelRenderer()
{
	this->shader = new AnimatedModelShader();
}

AnimatedModelRenderer::~AnimatedModelRenderer()
{
	delete shader;
}

void AnimatedModelRenderer::render(AnimatedModel* entity, Transform* camera, Matrix4* projection, Matrix4* modelview, Vector3f* lightDir)
{
	if (entity->getRootJoint() == nullptr)
	{
		shader->start();
	}
	else 
	{
		shader->startEnableAnimations();
	}

	prepare(camera, projection, modelview, lightDir);
	if (entity->getModel() != nullptr)
	{
		entity->getModel()->bind();
		entity->getModel()->binder(0, 6);
		std::vector<Matrix4*>* jointTransforms = entity->getJointTransforms();
		shader->jointTransforms->loadMatrixArray(shader->programID, jointTransforms);
		//glDrawArrays(GL_TRIANGLES, 0, entity->getModel()->verticiesCount);
		glDrawElements(GL_TRIANGLES, entity->getModel()->getIndexCount(), GL_UNSIGNED_INT, nullptr);
		entity->getModel()->unbind();
		entity->getModel()->unbinder(0, 6);
		finish();
	}
	else {
		std::cout << "Model not available to render." << std::endl;
	}
}

void AnimatedModelRenderer::prepare(Transform* camera, Matrix4* projection, Matrix4* modelview, Vector3f* lightDir)
{
	shader->projectionMatrix->loadMatrix(shader->programID, projection);
	shader->viewMatrix->loadMatrix(shader->programID, camera->localMatrix);
	shader->modelviewMatrix->loadMatrix(shader->programID, modelview);
	shader->lightDirection->loadVec3(shader->programID, lightDir);
	shader->eye->loadVec3(shader->programID, camera->localMatrix->GetTranslation());
	OpenGlUtils::Antialias(true);
	OpenGlUtils::DisableBlending();
	OpenGlUtils::EnableDepthTesting(true);
	//OpenGlUtils::GoWireframe(true);
}

void AnimatedModelRenderer::finish()
{
	shader->stop();
}