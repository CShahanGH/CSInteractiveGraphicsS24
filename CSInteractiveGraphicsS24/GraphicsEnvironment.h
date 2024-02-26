#pragma once
#include "BaseObject.h"
#include "Renderer.h"
#include <string>

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

class GraphicsEnvironment: public BaseObject
{
private: 
	GLFWwindow* window; 
	std::unordered_map<std::string, std::shared_ptr<Renderer>> rendererMap;

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
};



