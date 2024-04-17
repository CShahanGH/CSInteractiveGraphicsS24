#include "GeometricPlane.h"
#include "GeometricLine.h"
#include "Ray.h"

GeometricPlane::GeometricPlane() : normal(0, 1, 0), distanceFromOrigin(0)
{
}

void GeometricPlane::Set(glm::vec3 normal, float distance)
{
	SetIntersectionormal(normal);
	SetDistanceFromOrigin(distance);
}

Intersection GeometricPlane::GetIntersectionWithLine(
	const GeometricLine& line) const
{
	Intersection intersection;
	// Vince (2014) pp. 200
	float ndotv = glm::dot(normal, line.GetDirection());
	if (ndotv == 0) return intersection; // parallel
	float ndott = glm::dot(normal, line.GetStartPoint());
	float lambda = -(ndott + distanceFromOrigin) / ndotv;
	if (lambda < 0) return intersection; // miss, behind view point
	intersection.isIntersecting = true;
	intersection.point = line.GetPosition(lambda);
	return intersection;
}

float GeometricPlane::GetIntersectionOffset(const Ray& ray)
{
	float miss;
	float offset;
	float nRayProjection;
	float nStartProjection;

	miss = -1.0f;
	offset = miss;

	nRayProjection = glm::dot(normal, ray.GetDirection());
	if (nRayProjection == 0) { return miss; } //They are perpendicular
	nStartProjection = glm::dot(normal, ray.GetStart());
	offset = -(nStartProjection + distanceFromOrigin) / nRayProjection;
	// A negative value means the intersection offset is behind the start point
	return offset;
}
