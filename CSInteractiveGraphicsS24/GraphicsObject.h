#pragma once
#include <glm/glm.hpp>
#include <memory>
#include "IAnimation.h"
#include "VertexBuffer.h"
#include "GraphicsStructures.h"
#include "IndexBuffer.h"
#include "BoundingBox.h"
#include "IBehavior.h"

class GraphicsObject
{
protected:
	glm::mat4 referenceFrame;
	std::shared_ptr<VertexBuffer> buffer;
	GraphicsObject* parent;
	std::vector<std::shared_ptr<GraphicsObject>> children;
	std::shared_ptr<IAnimation> animation = nullptr;
	Material material;
	std::shared_ptr<IndexBuffer> indexBuffer = nullptr;
	std::shared_ptr<BoundingBox> boundingBox = nullptr;
	std::unordered_map<std::string, std::shared_ptr<IBehavior>> behaviorMap;
	bool moving = false;

public:
	GraphicsObject();
	virtual ~GraphicsObject();

	const glm::mat4 GetReferenceFrame() const;
	void CreateVertexBuffer(unsigned int numberOfElementsPerVertex);
	void SetVertexBuffer(std::shared_ptr<VertexBuffer> buffer);
	inline std::shared_ptr<VertexBuffer>& GetVertexBuffer() {
		return buffer;
	}
	void StaticAllocateBuffers();

	void AddChild(std::shared_ptr<GraphicsObject> child);
	inline const std::vector<std::shared_ptr<GraphicsObject>>& GetChildren() const {
		return children;
	}

	void SetPosition(const glm::vec3& position);
	void ResetOrientation();
	void RotateLocalZ(float degrees);

	void SetReferenceFrame(glm::mat4& referenceFrame) { this->referenceFrame = referenceFrame; } //Lab 5 Part  4

	void Update(double elapsedSeconds); //Lab 
	void SetAnimation(std::shared_ptr<IAnimation> animation) { this->animation = animation; }
	glm::mat4& GetLocalReferenceFrame() { return referenceFrame; }
	Material& GetMaterial() { return material; } //Lab 7
	void PointAt(const glm::vec3& point); //Lab 7

	void CreateIndexBuffer(); //Lab 8
	std::shared_ptr<IndexBuffer>& GetIndexBuffer() { return indexBuffer; }
	bool IsIndexed() const;

	void CreateBoundingBox(float width, float height, float depth); //lab 9
	const BoundingBox& GetBoundingBox() const { return *boundingBox; }
	bool IsIntersectingWithRay(const Ray& ray) const;

	void SetAmbientIntensity(float ambientIntensity) { material.ambientIntensity = ambientIntensity; }

	void AddBehavior(std::string name, std::shared_ptr<IBehavior> behavior) { behaviorMap[name] = behavior; }
	void SetBehaviorDefaults();
	void SetBehaviorParameters(std::string name, IParams& params);

	void ChangeMoving() { moving = !moving; }
	bool Moving() const { return moving; }
};

