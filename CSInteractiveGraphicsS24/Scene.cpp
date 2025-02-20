#include "Scene.h"

Scene::Scene()
{
	globalLight.position = glm::vec3(0.0f, 80.0f, 0.0f);
	globalLight.color = glm::vec3(1.0f, 1.0f, 1.0f); // White light
	globalLight.intensity = 0.5f;

	localLight.position = glm::vec3(0.0f, 5.0f, 8.0f);
	localLight.color = glm::vec3(1.0f, 1.0f, 1.0f); // White light
	localLight.intensity = 0.05f;
	localLight.attenuationCoef = 0.0f;
	
	trophyLight.position = glm::vec3(0.0f, 70.0f, 0.0f);
	globalLight.color = glm::vec3(1.0f, 1.0f, 0.9f); // Yellow light
	localLight.intensity = 0.01f;
	localLight.attenuationCoef = 0.5f;
}

void Scene::AddObject(std::shared_ptr<GraphicsObject> object)
{
	objects.push_back(object);
}
