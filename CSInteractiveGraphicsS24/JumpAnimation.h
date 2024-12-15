#pragma once
#include "IAnimation.h"
class JumpAnimation : public IAnimation
{
private:
	glm::vec3 direction;
	float speed;
	float distanceToMove;
	float distanceMoved = 0.0f;

public:
	JumpAnimation(glm::vec3 direction = glm::vec3(0.0f, 1.0f, 0.0f), float speed = 10.0f, float distance = 20.0f) : IAnimation(), direction(direction), speed(speed), distanceToMove(distance) {}
	void Update(double elapsedSeconds);
};

