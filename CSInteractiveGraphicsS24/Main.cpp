#include <Windows.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "VertexBuffer.h"
#include "GraphicsObject.h"
#include "Scene.h"
#include "Shader.h"
#include "Renderer.h"
#include "TextFile.h"
#include "GraphicsEnvironment.h"


void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

//Lab 4 
static void SetUpTexturedScene(std::shared_ptr<Shader>& textureShader, std::shared_ptr<Scene>& textureScene)
{
	//Read texture files and create a textureShader
	TextFile vertextFile("texture.vert.glsl");
	TextFile fragmentFile("texture.frag.glsl");
	std::string vertexSource = vertextFile.GetData();
	std::string fragmentSource = fragmentFile.GetData();
	textureShader = std::make_shared<Shader>(vertexSource, fragmentSource);

	//Add Unifroms
	textureShader->AddUniform("projection");
	textureShader->AddUniform("world");
	textureShader->AddUniform("view");
	textureShader->AddUniform("textUnit");

	//Create a new shared texture 
	std::shared_ptr<Texture> texture = std::make_shared<Texture>();

	//Set width and height to 4 
	texture->setHeight(4);
	texture->setWidth(4);
	
	//Set the texture data 
	unsigned char* textureData = new unsigned char[] {
			255, 255, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 255, 255, 255, 255,
			0, 255, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 255, 0, 255,
			0, 255, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 255, 0, 255,
			255, 255, 255, 255, 255, 0, 0, 255, 255, 0, 0, 255, 255, 255, 255, 255,
	};

	texture->setTextureData(64, textureData);
	
	//Part 8
	texture->setwrapS(GL_CLAMP_TO_EDGE);
	texture->setwrapT(GL_CLAMP_TO_EDGE);
	texture->setmagFilter(GL_LINEAR);

	//Shared scene object
	textureScene = std::make_shared<Scene>();

	//Shared graphics object 
	std::shared_ptr<GraphicsObject> object = std::make_shared<GraphicsObject>();

	//Shared VertexBuffer
	std::shared_ptr<VertexBuffer> buffer = std::make_shared<VertexBuffer>(8);

	//Add Vertex Data
	buffer->AddVertexData(8, -20.0f, 20.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 3.0f);
	buffer->AddVertexData(8, -20.0f, -20.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f);
	buffer->AddVertexData(8, 20.0f, -20.0f, 0.0f, 1.0f, 1.0f, 1.0f, 3.0f, 0.0f);
	buffer->AddVertexData(8, -20.0f, 20.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 3.0f);
	buffer->AddVertexData(8, 20.0f, -20.0f, 0.0f, 1.0f, 1.0f, 1.0f, 3.0f, 0.0f);
	buffer->AddVertexData(8, 20.0f, 20.0f, 0.0f, 1.0f, 1.0f, 1.0f, 3.0f, 3.0f);

	//Add vertex attributes
	buffer->AddVertexAttribute("position", 0, 3, 0);
	buffer->AddVertexAttribute("color", 1, 3, 3);
	buffer->AddVertexAttribute("texCoord", 2, 2, 6);
	
	//Set the buffer's texture
	buffer->setTexture(texture);

	//Set the object's buffer
	object->SetVertexBuffer(buffer);

	//Set the object's position
	object->SetPosition(glm::vec3(-35.0f, -20.0f, 0.0f));

	//Add object to the scene
	textureScene->AddObject(object);

	//Part 7 
	
	std::shared_ptr<Texture> texture2 = std::make_shared<Texture>();
	std::shared_ptr<GraphicsObject> object2 = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> buffer2 = std::make_shared<VertexBuffer>(8);

	std::string absolutepath = "..\\Textures\\kenney_isometric-miniature-bases\\Angle\\base_snow_flat_N.png";
	texture2->LoadTextureDataFromFile("base_grass_detail_S.png");

	buffer2->AddVertexData(8, -20.0f, 20.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f);
	buffer2->AddVertexData(8, -20.0f, -20.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f);
	buffer2->AddVertexData(8, 20.0f, -20.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	buffer2->AddVertexData(8, -20.0f, 20.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f);
	buffer2->AddVertexData(8, 20.0f, -20.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f);
	buffer2->AddVertexData(8, 20.0f, 20.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);

	buffer2->AddVertexAttribute("position", 0, 3, 0);
	buffer2->AddVertexAttribute("color", 1, 3, 3);
	buffer2->AddVertexAttribute("texCoord", 2, 2, 6);

	buffer2->setTexture(texture2);

	object2->SetVertexBuffer(buffer2);

	object2->SetPosition(glm::vec3(35.0f, 30.0f, 0.0f));

	textureScene->AddObject(object2);
}

//Lab 5
void SetUpScene1(std::shared_ptr<Shader>& shader, std::shared_ptr<Scene>& scene)
{
	//Read text files 
	TextFile vertextFile("basic.vert.glsl");
	TextFile fragmentFile("basic.frag.glsl");
	std::string vertexSource = vertextFile.GetData();
	std::string fragmentSource = fragmentFile.GetData();
	shader = std::make_shared<Shader>(vertexSource, fragmentSource);

	//Add Uniforms
	shader->AddUniform("projection");
	shader->AddUniform("world");
	shader->AddUniform("view");

	scene = std::make_shared<Scene>();

	std::shared_ptr<GraphicsObject> square = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> buffer = std::make_shared<VertexBuffer>(6);
	buffer->AddVertexData(6, -5.0f, 5.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	buffer->AddVertexData(6, -5.0f, -5.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	buffer->AddVertexData(6, 5.0f, -5.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	buffer->AddVertexData(6, -5.0f, 5.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	buffer->AddVertexData(6, 5.0f, -5.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	buffer->AddVertexData(6, 5.0f, 5.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	buffer->AddVertexAttribute("position", 0, 3);
	buffer->AddVertexAttribute("color", 1, 3, 3);
	square->SetVertexBuffer(buffer);
	scene->AddObject(square);

	std::shared_ptr<GraphicsObject> triangle = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> buffer2 = std::make_shared<VertexBuffer>(6);
	buffer2->AddVertexData(6, -5.0f, 5.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	buffer2->AddVertexData(6, -5.0f, -5.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	buffer2->AddVertexData(6, 5.0f, -5.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	buffer2->AddVertexAttribute("position", 0, 3);
	buffer2->AddVertexAttribute("color", 1, 3, 3);
	triangle->SetVertexBuffer(buffer2);
	triangle->SetPosition(glm::vec3(30.0f, 0.0f, 0.0f));
	scene->AddObject(triangle);

	std::shared_ptr<GraphicsObject> line = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> buffer3 = std::make_shared<VertexBuffer>(6);
	buffer3->SetPrimitiveType(GL_LINES);
	buffer3->AddVertexData(6, 0.0f, 2.5f, 0.0f, 0.0f, 1.0f, 0.0f);
	buffer3->AddVertexData(6, 0.0f, -2.5f, 0.0f, 0.0f, 1.0f, 0.0f);
	buffer3->AddVertexAttribute("position", 0, 3);
	buffer3->AddVertexAttribute("color", 1, 3, 3);
	line->SetVertexBuffer(buffer3);
	line->SetPosition(glm::vec3(5.0f, -10.0f, 0.0f));
	triangle->AddChild(line);
}


static glm::mat4 CreateViewMatrix(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& up)
{
	glm::vec3 right = glm::cross(direction, up);
	right = glm::normalize(right);

	glm::vec3 vUp = glm::cross(right, direction);
	vUp = glm::normalize(vUp);

	glm::mat4 view(1.0f);
	view[0] = glm::vec4(right, 0.0f);
	view[1] = glm::vec4(up, 0.0f);
	view[2] = glm::vec4(direction, 0.0f);
	view[3] = glm::vec4(position, 1.0f);
	return glm::inverse(view);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	//Lab 5
	GraphicsEnvironment glfw;

	glfw.Init(4, 3);

	bool created = glfw.SetWindow(1200, 800, "ETSU Computing Interactive Graphics");
	if (created == false) return -1;
	
	bool loaded = glfw.InitGlad();
	if (loaded == false) return -1;

	glfw.SetupGraphics();

	//Lab 5 Part 2
	std::shared_ptr<Shader> shader;
	std::shared_ptr<Scene> scene;
	SetUpScene1(shader, scene);

	std::shared_ptr<Shader> textureShader;
	std::shared_ptr<Scene> textureScene;
	SetUpTexturedScene(textureShader, textureScene);

	glfw.CreateRenderer("renderer", shader);
	glfw.GetRenderer("renderer")->SetScene(scene);
	glfw.CreateRenderer("textureRenderer", textureShader);
	glfw.GetRenderer("textureRenderer")->SetScene(textureScene);

	glfw.staticAllocate();

	GLFWwindow* window = glfw.GetWindow();

	//Needed Lab 5 Part 2 1.43
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	float aspectRatio = width / (height * 1.0f);

	float left = -50.0f;
	float right = 50.0f;
	float bottom = -50.0f;
	float top = 50.0f;
	left *= aspectRatio;
	right *= aspectRatio;
	glm::mat4 projection = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
	//Needed

	glm::vec3 clearColor = { 0.2f, 0.3f, 0.3f };

	float angle = 0, childAngle = 0;
	float cameraX = -10, cameraY = 0;
	glm::mat4 view;

	//Lab 5 Part 1
	ImGuiIO& io = ImGui::GetIO();

	while (!glfwWindowShouldClose(window)) {
		ProcessInput(window);

		glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		view = CreateViewMatrix(
			glm::vec3(cameraX, cameraY, 1.0f),
			glm::vec3(0.0f, 0.0f, -1.0f),
			glm::vec3(0.0f, 1.0f, 0.0f)
		);
	
		//Lab 4
		/*
		renderer->SetScene(scene);
		renderer->SetView(view);
		renderer->SetProjection(projection);
		renderer->RenderScene();

		
		textureRenderer->SetScene(textureScene);
		textureRenderer->SetView(view);
		textureRenderer->SetProjection(projection);
		textureRenderer->RenderScene();
		*/

		//Lab 5
		glfw.GetRenderer("renderer")->SetView(view);
		glfw.GetRenderer("renderer")->SetProjection(projection);
		glfw.GetRenderer("renderer")->RenderScene();

		glfw.GetRenderer("textureRenderer")->SetView(view);
		glfw.GetRenderer("textureRenderer")->SetProjection(projection);
		glfw.GetRenderer("textureRenderer")->RenderScene();

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("Computing Interactive Graphics");
		ImGui::Text(shader->GetLog().c_str());
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
			1000.0f / io.Framerate, io.Framerate);
		ImGui::ColorEdit3("Background color", (float*)&clearColor.r);
		ImGui::SliderFloat("Angle", &angle, 0, 360);
		ImGui::SliderFloat("Child Angle", &childAngle, 0, 360);
		ImGui::SliderFloat("Camera X", &cameraX, left, right);
		ImGui::SliderFloat("Camera Y", &cameraY, bottom, top);
		ImGui::End();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}

