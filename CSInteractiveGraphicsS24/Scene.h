#pragma once
#include <memory>
#include <vector>
#include "GraphicsObject.h"
#include "GraphicsStructures.h"

class Scene
{
private:
	std::vector<std::shared_ptr<GraphicsObject>> objects;
	Light globalLight;
	Light localLight;
	Light trophyLight;

public:
	Scene();
	~Scene() = default;
	inline const std::vector<std::shared_ptr<GraphicsObject>>& GetObjects() const {
		return objects;
	}
	void AddObject(std::shared_ptr<GraphicsObject> object);
	Light& GetGlobalLight() { return globalLight; } //Lab 7
	Light& GetLocalLight() { return localLight; } //Lab 7
	Light& GetTrophyLight() { return trophyLight; }
};

