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
	bool lookwithmouse = false; //lab 7

		
public: 
	Camera();
	~Camera();

	void SetLookFrame(glm::mat4 lookframe) { this->lookframe = lookframe; }
	glm::mat4 GetLookFrame() { return lookframe; }
	void SetMoveSpeed(float movespeed) { this->movespeed = movespeed;  }
	void SetPosition(glm::vec3 position) { this->referenceframe[3] = glm::vec4(position, 1.0f); }

	bool LookWithMouse() { return lookwithmouse; }

	void MoveForward(double elpasedSeconds);
	void MoveBackward(double elapsedSeconds);
	void MoveLeft(double elapsedSeconds);
	void MoveRight(double elapsedSeconds);
	void MoveUp(double elapsedSeconds);
	void MoveDown(double elapsedSeconds);
	
	void ToggleMouse();

	glm::mat4 LookForward();
	//Lab 7 
	glm::mat4 LookRight();
	glm::mat4 LookLeft();
	glm::mat4 LookBehind();

	glm::mat4 LookAt(glm::vec3 cameraTarget);
};

