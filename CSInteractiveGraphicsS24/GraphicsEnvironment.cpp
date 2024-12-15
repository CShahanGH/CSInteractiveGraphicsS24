#include "GraphicsEnvironment.h"
#include "GraphicsStructures.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "Timer.h"
#include "RotateAnimation.h"
#include "ObjectManager.h"
#include "MoveAnimation.h"

GraphicsEnvironment* GraphicsEnvironment::self;

GraphicsEnvironment::GraphicsEnvironment()
{
	window = 0;
	objectManager = std::make_shared<ObjectManager>();
	camera = std::make_shared<Camera>();
	self = this;
}

GraphicsEnvironment::~GraphicsEnvironment()
{
	glfwTerminate();
}

void GraphicsEnvironment::Init(unsigned int majorVersion, unsigned int minorVersion)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4); //Lab 5 Part 7
}

bool GraphicsEnvironment::SetWindow(unsigned int width, unsigned int height, const std::string& title)
{
	window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (window == NULL) {
		Log("Failed to create GLFW window");
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	return true;
}

bool GraphicsEnvironment::InitGlad()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		Log("Failed to initialize GLAD");
		return false;
	}
	return true;
}

void GraphicsEnvironment::SetupGraphics()
{
	//Lab 4 Part 7 enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Cull back faces and use counter-clockwise winding of front faces
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	// Enable depth testing
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);

	//Enable Multisampling 
	glEnable(GL_MULTISAMPLE);

	glfwSetFramebufferSizeCallback(window, OnWindowSizeChanged);
	//glfwSetCursorPosCallback(window, OnMouseMove); 
	//glfwSetMouseButtonCallback(window, OnButtonClick);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 430");
}

void GraphicsEnvironment::OnWindowSizeChanged(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	//glfwMaximizeWindow(window);

}

void GraphicsEnvironment::CreateRenderer(const std::string& name, std::shared_ptr<Shader> shader)
{
	std::shared_ptr<Renderer> renderer = std::make_shared<Renderer>(shader);
	rendererMap[name] = renderer;
}

void GraphicsEnvironment::staticAllocate()
{
	for (const auto& [name, renderer] : rendererMap) {
		std::shared_ptr<Scene> scene = renderer->GetScene();
		auto& Objects = scene->GetObjects();
		renderer->AllocateVertexBuffers(Objects);
	}
}

void GraphicsEnvironment::Render()
{
	for (const auto& [name, renderer] : rendererMap) {
		renderer->RenderScene(*camera);
	}
}

void GraphicsEnvironment::ProcessInput(GLFWwindow* window, double elapsedSeconds, glm::mat4& view)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera->MoveForward(elapsedSeconds);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera->MoveBackward(elapsedSeconds);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera->MoveLeft(elapsedSeconds);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera->MoveRight(elapsedSeconds);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		camera->RotateLeft(elapsedSeconds);
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		camera->RotateRight(elapsedSeconds);
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		camera->RotateUp(elapsedSeconds);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		camera->RotateDown(elapsedSeconds);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		Jump();
	}
	if (glfwGetKey(window, GLFW_KEY_F3) == GLFW_PRESS)
	{
		debugging = !debugging;
	}
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		glm::mat4 lookframe(1.0f);
		camera->SetLookFrame(lookframe);
	}
}

glm::mat4 GraphicsEnvironment::CreateViewMatrix(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& up)
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

void GraphicsEnvironment::Run3D()
{
	int width, height;


	float aspectRatio;
	float nearPlane = 1.0f;
	float farPlane = 100.0f;
	float fieldOfView = 60;

	//Camera Position
	glm::vec3 startingPosition(1.0f, 5.0f, 1.0f);
	camera->SetPosition(startingPosition);
	glm::vec3 cameraTarget(0.0f, 0.0f, 0.0f);

	glm::mat4 view = camera->LookForward();
	glm::mat4 projection;
	glm::mat4 referenceFrame(1.0f);
	glm::vec3 clearColor = { 0.3f, 0.7f, 0.7f };

	ImGuiIO& io = ImGui::GetIO();

	Timer timer;
	double elapsedSeconds;

	objectManager->SetBehaviorDefaults();

	while (!glfwWindowShouldClose(window)) {
		elapsedSeconds = timer.GetElapsedTimeInSeconds();

		ProcessInput(window, elapsedSeconds, view);
		glfwGetWindowSize(window, &width, &height);

		mouse.windowWidth = width;
		mouse.windowHeight = height;

		glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		view = camera->LookForward();

		//Day night cycle? 
		Light& globallight = GetRenderer("level1renderer")->GetScene()->GetGlobalLight();
		if (day)
		{
			globallight.intensity = globallight.intensity - 0.00001f;
			if (globallight.intensity <= 0.1f)
				day = false;
		}
		else
		{
			globallight.intensity = globallight.intensity + 0.00001f;
			if (globallight.intensity >= 0.5f)
				day = true;
		}
		
		
		//Set Trophy Position 
		objectManager->GetObject("Trophy")->SetPosition(GetRenderer("level1renderer")->GetScene()->GetTrophyLight().position);
		objectManager->GetObject("Trophy")->PointAt(camera->GetPosition());

		if (width >= height) {
			aspectRatio = width / (height * 1.0f);
		}
		else {
			aspectRatio = height / (width * 1.0f);
		}
		projection = glm::perspective(
			glm::radians(fieldOfView), aspectRatio, nearPlane, farPlane);

		//Make Camera Fall 
		CheckCameraBox();
		Falling(elapsedSeconds);
		if (camera->GetPosition()[1] < -10.0f)
		{
			camera->SetPosition(startingPosition);
		}

		objectManager->Update(elapsedSeconds);

		// Render the scene (cuboid, crate, floor) 
		GetRenderer("level1renderer")->SetView(view);
		GetRenderer("level1renderer")->SetProjection(projection);
		GetRenderer("level1renderer")->RenderScene(*camera);

		//Lab 7 Render the lightbulb 
		GetRenderer("trophyrenderer")->SetView(view);
		GetRenderer("trophyrenderer")->SetProjection(projection);
		GetRenderer("trophyrenderer")->RenderScene(*camera);

		//IMGUI
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("Computing Interactive Graphics");
		ImGui::Text("Press 1 To Look North");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
			1000.0f / io.Framerate, io.Framerate);
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
	return;
}

void GraphicsEnvironment::AddObject(const std::string& name, std::shared_ptr<GraphicsObject> object)
{
	objectManager->SetObject(name, object);
}

void GraphicsEnvironment::CheckCameraBox()
{
	auto map = objectManager->GetMap();
	for (const auto& [name, object] : map) {
		if (camera->OverlapsWithObject(object))
		{
			playerFall = false;
			if (name == "Trophy")
			{
				camera->SetPosition(glm::vec3(1.0f, 0.5f, 1.0f));
			}
			return;

		}
	}
	playerFall = true;
}

void GraphicsEnvironment::Falling(double elapsedSeconds)
{
	if (playerFall)
	{
		camera->FallDown(elapsedSeconds);
	}
}

void GraphicsEnvironment::Jump()
{
	if (playerFall)
	{
		return;
	}
	camera->Jump();
}

