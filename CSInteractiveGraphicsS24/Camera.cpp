#include "Camera.h"
#include <glm/ext/matrix_transform.hpp>

Camera::Camera(): referenceframe(1.0f), lookframe(1.0f)
{

}

Camera::~Camera()
{
}

void Camera::MoveForward(double elapsedSeconds)
{
	glm::vec3 forward = -lookframe[2];
	glm::vec3 position = referenceframe[3];
	forward = forward * static_cast<float>(movespeed * elapsedSeconds);
	position = position + forward;
	referenceframe[3] = glm::vec4(position, 1.0f);
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

void Camera::MoveUp(double elapsedSeconds)
{
	glm::vec3 moveup = referenceframe[1];
	glm::vec3 position = referenceframe[3];
	moveup = moveup * static_cast<float>(movespeed * elapsedSeconds);
	position = position + moveup;
	referenceframe[3] = glm::vec4(position, 1.0f);
	return;
}

void Camera::MoveDown(double elapsedSeconds)
{
	glm::vec3 movedown = -referenceframe[1];
	glm::vec3 position = referenceframe[3];
	movedown = movedown * static_cast<float>(movespeed * elapsedSeconds);
	position = position + movedown;
	referenceframe[3] = glm::vec4(position, 1.0f);
	return;
}

glm::mat4 Camera::LookRight()
{
	glm::mat4 view;

	glm::vec3 cameraPosition = referenceframe[3];
	glm::vec3 cameraRight = -lookframe[0];
	glm::vec3 cameraTarget = cameraPosition + cameraRight;
	glm::vec3 cameraUp = lookframe[1];
	view = glm::lookAt(cameraPosition, cameraTarget, cameraUp);

	return view;
}

glm::mat4 Camera::LookLeft()
{
	glm::mat4 view;

	glm::vec3 cameraPosition = referenceframe[3];
	glm::vec3 cameraLeft = lookframe[0];
	glm::vec3 cameraTarget = cameraPosition + cameraLeft;
	glm::vec3 cameraUp = lookframe[1];
	view = glm::lookAt(cameraPosition, cameraTarget, cameraUp);

	return view;
}

glm::mat4 Camera::LookBehind()
{
	glm::mat4 view;

	glm::vec3 cameraPosition = referenceframe[3];
	glm::vec3 cameraBehind = lookframe[2];
	glm::vec3 cameraTarget = cameraPosition + cameraBehind;
	glm::vec3 cameraUp = lookframe[1];
	view = glm::lookAt(cameraPosition, cameraTarget, cameraUp);

	return view;
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

glm::mat4 Camera::LookAt(glm::vec3 cameraTarget)
{
	glm::mat4 view; 
	glm::vec3 cameraPosition = referenceframe[3];
	glm::vec3 cameraUp = lookframe[1];
	view = glm::lookAt(cameraPosition, cameraTarget, cameraUp);

	return view;
}
