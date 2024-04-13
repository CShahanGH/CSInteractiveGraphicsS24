#pragma once
#include "VertexBuffer.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "IndexBuffer.h"

class Generate
{
private:

public:
	Generate();
	~Generate();

	static std::shared_ptr<VertexBuffer> Cuboid(float width, float height, float depth, glm::vec3 color = { 1.0f, 1.0f, 1.0f }, glm::vec2 tex = { 1.0f, 1.0 });

	static std::shared_ptr<VertexBuffer> XZPlane(float width, float depth, glm::vec3 color = { 1.0f, 1.0f, 1.0f }, glm::vec2 tex = { 1.0f, 1.0 });

	static std::shared_ptr<VertexBuffer> XYPlane(float width, float depth, glm::vec3 color = { 1.0f, 1.0f, 1.0f }, glm::vec2 tex = { 1.0f, 1.0 });

	//Lab 7
	static std::shared_ptr<VertexBuffer> CuboidWithNormals(float width, float height, float depth, glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f }, glm::vec2 tex = { 1.0f, 1.0 });

	static std::shared_ptr<VertexBuffer> XZPlaneWithNormals(float width, float depth, glm::vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f }, glm::vec2 tex = { 1.0f, 1.0 });

	//Lab 8
	static void XZLineCircle(std::shared_ptr<VertexBuffer>& buffer, float radius, glm::vec3  color = { 1.0f, 1.0f, 1.0f }, int steps = 10);
	static void LineCircleIndexes(std::shared_ptr<IndexBuffer>& bufferToFill, int numberOfLineSegments, bool isClosed = true);
	static void LineCylinder(std::shared_ptr<VertexBuffer>& buffer, float radius, float height, glm::vec3 color = { 1.0f, 1.0f, 1.0f }, int steps = 10);
	static void LineCylinderIndexes(std::shared_ptr<IndexBuffer>& bufferToFill, int numberOfLineSegments);
};

