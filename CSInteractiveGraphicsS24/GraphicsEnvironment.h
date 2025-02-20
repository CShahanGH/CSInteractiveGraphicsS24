#pragma once
#include "BaseObject.h"
#include "Renderer.h"
#include "ObjectManager.h"
#include "Camera.h"
#include "GraphicsStructures.h"
#include "Ray.h"
#include <string>

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

class GraphicsEnvironment: public BaseObject
{
private: 
	GLFWwindow* window; 
	std::unordered_map<std::string, std::shared_ptr<Renderer>> rendererMap;
	std::shared_ptr<ObjectManager> objectManager;
	std::shared_ptr<Camera> camera;
	static GraphicsEnvironment* self;
	MouseParams mouse; 
	Ray ray;
	bool debugging = false; 
	bool playerFall = true;
	bool day = true;

public: 
	GraphicsEnvironment();
	~GraphicsEnvironment();

	GLFWwindow* GetWindow() const  { return window; }

	std::shared_ptr<Renderer> GetRenderer(const std::string& name) { return rendererMap[name]; }

	void Init(unsigned int majorVersion, unsigned int minorVersion);

	bool SetWindow(unsigned int width, unsigned int height, const std::string& title);

	bool InitGlad();

	void SetupGraphics();

	static void OnWindowSizeChanged(GLFWwindow* window, int width, int height);

	void CreateRenderer(const std::string& name, std::shared_ptr<Shader> shader);

	void staticAllocate();

	void Render();

	void ProcessInput(GLFWwindow* window, double elapsedSeconds, glm::mat4& view);

	static glm::mat4 CreateViewMatrix(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& up);

	void Run2D();

	void Run3D();

	void AddObject(const std::string& name, std::shared_ptr<GraphicsObject> object);

	static void OnMouseMove(GLFWwindow* window, double mouseX, double mouseY);

	static void OnButtonClick(GLFWwindow* window, int button, int action, int mods);

	Ray GetMouseRay(const glm::mat4& projection, const glm::mat4& view);

	void CheckCameraBox();

	void Falling(double elapsedSeconds);

	void Jump();
};



