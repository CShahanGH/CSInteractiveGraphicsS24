#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "BoundingBox.h"
#include "GraphicsObject.h"
#include <memory>

class Camera
{
private:
	glm::mat4 lookframe; 
	glm::mat4 referenceframe; 
	float movespeed = 10.0f;
	bool lookwithmouse = true; 
	std::shared_ptr<BoundingBox> boundingBox = nullptr;

		
public: 
	Camera();
	~Camera();

	void SetLookFrame(glm::mat4 lookframe) { this->lookframe = lookframe; }
	glm::mat4 GetLookFrame() { return lookframe; }
	void SetMoveSpeed(float movespeed) { this->movespeed = movespeed;  }
	void SetPosition(glm::vec3 position) { this->referenceframe[3] = glm::vec4(position, 1.0f); }
	glm::vec3 GetPosition() const { return referenceframe[3]; }

	bool LookWithMouse() { return lookwithmouse; }

	void MoveForward(double elpasedSeconds);
	void MoveBackward(double elapsedSeconds);
	void MoveLeft(double elapsedSeconds);
	void MoveRight(double elapsedSeconds);

	void RotateLeft(double elapsedSeconds);
	void RotateRight(double elapsedSeconds);

	void MoveUp(double elapsedSeconds);

	void FallDown(double elapsedSeconds);
	void Jump(double elapsedSeconds);
	
	void ToggleMouse();

	glm::mat4 LookForward();
	
	void CreateBoundingBox(float width, float height, float depth); 
	const BoundingBox& GetBoundingBox() const { return *boundingBox; }

	bool OverlapsWithObject(const std::shared_ptr<GraphicsObject>& object);

	glm::mat4 LookAt(glm::vec3 cameraTarget);
};

