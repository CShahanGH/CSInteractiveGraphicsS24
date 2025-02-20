#pragma once
#include <glm/fwd.hpp>
#include "GeometricPlane.h"
#include <vector>
#include "Ray.h"

struct MinMax {
	float min = 0.0f;
	float max = 0.0f;
};

class BoundingBox
{
public:
	static const int FRONT = 0;
	static const int BACK = 1;
	static const int LEFT = 2;
	static const int RIGHT = 3;
	static const int TOP = 4;
	static const int BOTTOM = 5;

protected:
	float width = 1.0f, height = 1.0f, depth = 1.0f;
	glm::mat4 frame;
	glm::mat4 invFrame;
	GeometricPlane planes[6];
	std::vector<float> intersections;
	glm::vec3 intersectionPoint{};

public:
	void SetReferenceFrame(glm::mat4 frameIn)
	{
		frame = frameIn;
		invFrame = glm::inverse(frame);
	}
	const glm::mat4& GetReferenceFrame() const { return frame; }
	const glm::vec3& GetIntersectionPoint() const { return intersectionPoint; }
	void Create(float width, float height, float depth);
	bool isIntersectingWithRay(const Ray& ray);
	MinMax GetMinMaxProjection(const glm::vec3& axis) const;
	bool OverLapsWith(const BoundingBox& other) const;
	bool OnTopOf(const BoundingBox& other) const;
};



