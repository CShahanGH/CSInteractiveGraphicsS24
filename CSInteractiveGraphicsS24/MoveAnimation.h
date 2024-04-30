#pragma once
#include "IAnimation.h"
#include <glm/glm.hpp>
class MoveAnimation : public IAnimation
{
private:
	glm::vec3 direction;
	float speed;
	float distanceToMove;
	float distanceMoved = 0.0f;

public:
	MoveAnimation(glm::vec3 direction = glm::vec3(0.0f, 0.0f, -1.0f), float speed = 10.0f, float distance = 20.0f) : IAnimation(), direction(direction), speed(speed), distanceToMove(distance) {}
	void Update(double elapsedSeconds);
};


