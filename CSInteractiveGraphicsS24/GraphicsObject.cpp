#include "GraphicsObject.h"
#include <glm/gtc/matrix_transform.hpp>

GraphicsObject::GraphicsObject() : referenceFrame(1.0f), parent(nullptr), material{ 0.1f, 0.5f ,16.0f }
{
	CreateBoundingBox(1.0f, 1.0f, 1.0f);
}

GraphicsObject::~GraphicsObject()
{
}

const glm::mat4 GraphicsObject::GetReferenceFrame() const
{
	if (parent != nullptr) {
		return parent->referenceFrame * referenceFrame;
	}
	return referenceFrame;
}

void GraphicsObject::CreateVertexBuffer(unsigned int numberOfElementsPerVertex)
{
	buffer = std::make_shared<VertexBuffer>(numberOfElementsPerVertex);
}

void GraphicsObject::SetVertexBuffer(std::shared_ptr<VertexBuffer> buffer)
{
	this->buffer = buffer;
}

void GraphicsObject::StaticAllocateBuffers()
{
	if (indexBuffer != nullptr)
	{
		indexBuffer->Select();
		indexBuffer->StaticAllocate();
		indexBuffer->Deselect();
	}
	buffer->Select();
	buffer->StaticAllocate();
	buffer->Deselect();
	for (auto& child : children) {
		child->StaticAllocateBuffers();
	}
}

void GraphicsObject::AddChild(std::shared_ptr<GraphicsObject> child)
{
	children.push_back(child);
	child->parent = this;
}

void GraphicsObject::SetPosition(const glm::vec3& position)
{
	referenceFrame[3] = glm::vec4(position, 1.0f);
}

void GraphicsObject::ResetOrientation()
{
	glm::vec4 position = referenceFrame[3];
	referenceFrame = glm::mat4(1.0f);
	referenceFrame[3] = position;
}

void GraphicsObject::RotateLocalZ(float degrees)
{
	referenceFrame = glm::rotate(
		referenceFrame, 
		glm::radians(degrees), 
		glm::vec3(0.0f, 0.0f, 1.0f)
	);
}

void GraphicsObject::Update(double elapsedSeconds)
{
	if (animation != nullptr)
	{
		animation->Update(elapsedSeconds);
	}
	for (const auto& [name, behavior] : behaviorMap)
	{
		behavior->Update(elapsedSeconds);
	}
}

void GraphicsObject::PointAt(const glm::vec3& point)
{
	glm::vec3 position = referenceFrame[3];
	glm::vec3 zAxis = glm::normalize(point - position);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 xAxis = glm::normalize(glm::cross(up, zAxis));
	glm::vec3 yAxis = glm::cross(zAxis, xAxis);
	referenceFrame[0] = glm::vec4(xAxis, 0.0f);
	referenceFrame[1] = glm::vec4(yAxis, 0.0f);
	referenceFrame[2] = glm::vec4(zAxis, 0.0f);
}

void GraphicsObject::CreateIndexBuffer()
{
	indexBuffer = std::make_shared<IndexBuffer>();
}

bool GraphicsObject::IsIndexed() const
{
	if (indexBuffer != nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void GraphicsObject::CreateBoundingBox(float width, float height, float depth)
{
	boundingBox = std::make_shared<BoundingBox>();
	boundingBox->SetReferenceFrame(referenceFrame);
	boundingBox->Create(width, height, depth);
}

bool GraphicsObject::IsIntersectingWithRay(const Ray& ray) const
{
	boundingBox->SetReferenceFrame(referenceFrame);
	return boundingBox->isIntersectingWithRay(ray);
}

void GraphicsObject::SetBehaviorDefaults()
{
	for (const auto& [name, behavior] : behaviorMap)
	{
		behavior->StoreDefaults();
	}
}

void GraphicsObject::SetBehaviorParameters(std::string name, IParams& params)
{
	behaviorMap[name]->SetParameter(params);
}

bool GraphicsObject::hasBoundingBox()
{
	if(boundingBox != nullptr)
		return true;
	return false;
}



