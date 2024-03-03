#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
}

void ObjectManager::SetObject(const std::string& name, std::shared_ptr<GraphicsObject> object)
{
	objectMap[name] = object;
}

void ObjectManager::Update(double elapsedSeconds)
{
	for (const auto& [name, object] : objectMap) {
		object->Update(elapsedSeconds);
	}
}
