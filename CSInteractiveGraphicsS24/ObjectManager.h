#pragma once
#include "BaseObject.h"
#include "GraphicsObject.h"

class ObjectManager: public BaseObject
{
private: 
	std::unordered_map<std::string, std::shared_ptr<GraphicsObject>> objectMap;
	
public:
	ObjectManager();
	~ObjectManager();

	std::unordered_map<std::string, std::shared_ptr<GraphicsObject>> GetMap() { return objectMap; }

	std::shared_ptr<GraphicsObject> GetObject(const std::string& name) { return objectMap[name]; }

	void SetObject(const std::string& name, std::shared_ptr<GraphicsObject> object);

	void Update(double elapsedSeconds);

	void SetBehaviorDefaults();

};

