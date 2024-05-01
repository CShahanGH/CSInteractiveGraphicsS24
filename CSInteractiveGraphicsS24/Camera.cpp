#include "Camera.h"
#include <glm/ext/matrix_transform.hpp>

Camera::Camera(): referenceframe(1.0f), lookframe(1.0f)
{
	CreateBoundingBox(1.0f, 5.0f, 1.0f);
}

Camera::~Camera()
{
}

void Camera::MoveForward(double elapsedSeconds)
{
	float zforward = -lookframe[2][2]; //Get Z Direction
	float zposition = referenceframe[3][2]; //Get Z Position;
	zforward = zforward * static_cast<float>(movespeed * elapsedSeconds); //Update direction 
	zposition = zposition + zforward; //Update Z Position
	referenceframe[3][2] = zposition; //Save Z Position
	float xforward = -lookframe[2][0]; //Get X Direction
	float xposition = referenceframe[3][0]; //Get Z Position;
	xforward = xforward * static_cast<float>(movespeed * elapsedSeconds); //Update direction 
	xposition = xposition + xforward; //Update X Position
	referenceframe[3][0] = xposition; //Save X Position
	return;
}

void Camera::MoveBackward(double elapsedSeconds)
{
	glm::vec3 backward = lookframe[2];
	glm::vec3 position = referenceframe[3];
	backward = backward * static_cast<float>(movespeed * elapsedSeconds);
	position = position + backward;
	referenceframe[3] = glm::vec4(position, 1.0f);
	return; 
}

void Camera::MoveLeft(double elapsedSeconds)
{
	glm::vec3 toLeft = -lookframe[0];
	glm::vec3 position = referenceframe[3];
	toLeft = toLeft * static_cast<float>(movespeed * elapsedSeconds);
	position = position + toLeft;
	referenceframe[3] = glm::vec4(position, 1.0f);
	return;
}

void Camera::MoveRight(double elapsedSeconds)
{
	glm::vec3 toRight = lookframe[0];
	glm::vec3 position = referenceframe[3];
	toRight = toRight * static_cast<float>(movespeed * elapsedSeconds);
	position = position + toRight;
	referenceframe[3] = glm::vec4(position, 1.0f);
	return;
}

void Camera::RotateLeft(double elapsedSeconds)
{
	float speed = 60.0f;
	float deltaSpeed = static_cast<float>(speed * elapsedSeconds);
	lookframe = glm::rotate(lookframe, glm::radians(deltaSpeed), { 0, 1, 0 });
}

void Camera::RotateRight(double elapsedSeconds)
{
	float speed = -60.0f;
	float deltaSpeed = static_cast<float>(speed * elapsedSeconds);
	lookframe = glm::rotate(lookframe, glm::radians(deltaSpeed), { 0, 1, 0 });
}

void Camera::MoveUp(double elapsedSeconds)
{
	glm::vec3 moveup = referenceframe[1];
	glm::vec3 position = referenceframe[3];
	moveup = moveup * static_cast<float>(movespeed * elapsedSeconds);
	position = position + moveup;
	referenceframe[3] = glm::vec4(position, 1.0f);
	return;
}

void Camera::FallDown(double elapsedSeconds)
{
	glm::vec3 movedown = -referenceframe[1];
	glm::vec3 position = referenceframe[3];
	float fallspeed = 10.0f;
	movedown = movedown * static_cast<float>(fallspeed * elapsedSeconds);
	position = position + movedown;
	referenceframe[3] = glm::vec4(position, 1.0f);
	return;
}

void Camera::Jump(double elapsedSeconds)
{
	glm::vec3 moveup = referenceframe[1];
	glm::vec3 position = referenceframe[3];
	float jumpspeed = 100.0f; 
	float deltaspeed = static_cast<float>(jumpspeed * elapsedSeconds);
	moveup = moveup * deltaspeed;
	position = position + moveup;
	referenceframe[3] = glm::vec4(position, 1.0f);
	return;
}

void Camera::ToggleMouse()
{
	lookwithmouse = !lookwithmouse;
	return;
}

glm::mat4 Camera::LookForward()
{
	glm::mat4 view; 

	glm::vec3 cameraPosition = referenceframe[3];
	glm::vec3 cameraForward = -lookframe[2];
	glm::vec3 cameraTarget = cameraPosition + cameraForward;
	glm::vec3 cameraUp = lookframe[1];
	view = glm::lookAt(cameraPosition, cameraTarget, cameraUp);

	return view;
}

void Camera::CreateBoundingBox(float width, float height, float depth)
{
	boundingBox = std::make_shared<BoundingBox>();
	boundingBox->SetReferenceFrame(referenceframe);
	boundingBox->Create(width, height, depth);
}

bool Camera::OverlapsWithObject(const std::shared_ptr<GraphicsObject>& object)
{
	if (object->hasBoundingBox())
	{
		boundingBox->SetReferenceFrame(referenceframe);
		object->setBoundingBoxFrame(); 
		return boundingBox->OverLapsWith(object->GetBoundingBox());
	}
	return false;
}

glm::mat4 Camera::LookAt(glm::vec3 cameraTarget)
{
	glm::mat4 view; 
	glm::vec3 cameraPosition = referenceframe[3];
	glm::vec3 cameraUp = lookframe[1];
	view = glm::lookAt(cameraPosition, cameraTarget, cameraUp);

	return view;
}
