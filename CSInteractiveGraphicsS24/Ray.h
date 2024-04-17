#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "GeometricPlane.h"


class Ray
{
protected:
	glm::vec3 rayStart{};
	glm::vec3 rayDir{};

public:
	Ray() = default;
	~Ray() = default;
	void Create(
		float screenX, float screenY,
		const glm::mat4& proj, const glm::mat4& view);

	void SetStart(glm::vec3 start)
	{
		rayStart = start;
	}
	void SetDirection(glm::vec3 direction)
	{
		rayDir = direction; 
	}
	const glm::vec3& GetStart() const { return rayStart; }
	const glm::vec3& GetDirection() const { return rayDir; }

	glm::vec3 GetPoint(float offset) const { return rayStart + (offset * rayDir); }

	Intersection GetIntersectionWithPlane(const GeometricPlane& plane) const;
};

