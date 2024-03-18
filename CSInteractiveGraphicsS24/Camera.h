#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Camera
{
private:
	glm::mat4 lookframe; 
	glm::mat4 referenceframe; 
	float movespeed = 10.0f;

		
public: 
	Camera();
	~Camera();

	void SetLookFrame(glm::mat4 lookframe) { this->lookframe = lookframe; }
	void SetMoveSpeed(float movespeed) { this->movespeed = movespeed;  }
	void SetPosition(glm::vec3 position) { this->referenceframe[3] = glm::vec4(position, 1.0f); }

	void MoveForward(double elpasedSeconds);
	void MoveBackward(double elapsedSeconds);
	void MoveLeft(double elapsedSeconds);
	void MoveRight(double elapsedSeconds);
	void MoveUp(double elapsedSeconds);
	void MoveDown(double elapsedSeconds);

	glm::mat4 LookForward();

	glm::mat4 LookAt(glm::vec3 cameraTarget);
};

