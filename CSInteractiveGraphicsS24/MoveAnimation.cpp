#include "MoveAnimation.h"
#include "GraphicsObject.h"
#include <glm/gtc/matrix_transform.hpp>

void MoveAnimation::Update(double elapsedSeconds)
{
	if (object == nullptr) return;

	if (distanceMoved >= distanceToMove)
	{
		object->ChangeMoving();
		distanceMoved = 0.0f;
		direction = -direction;
	}

	if (object->Moving())
	{
		float deltaSpeed = static_cast<float>(speed * elapsedSeconds);
		auto& referenceFrame = object->GetLocalReferenceFrame();
		glm::vec3 position = { referenceFrame[3].x, referenceFrame[3].y, referenceFrame[3].z };
		position = position + (direction * deltaSpeed); //calculate new position;
		//update position
		referenceFrame[3].x = position.x; 
		referenceFrame[3].y = position.y;
		referenceFrame[3].z = position.z;
		distanceMoved = distanceMoved + deltaSpeed;
	}
}
