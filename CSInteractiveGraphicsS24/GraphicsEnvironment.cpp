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
	glfwSetCursorPosCallback(window, OnMouseMove); //Can't use IMGUI 

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
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		camera->MoveUp(elapsedSeconds);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		camera->MoveDown(elapsedSeconds);
	}
	//lab 7
	if (glfwGetKey(window, GLFW_KEY_F2) == GLFW_PRESS)
	{
		camera->ToggleMouse();
	}
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		glm::vec3 cameraPosition(0.0f, 5.0f, 30.0f);
		camera->SetPosition(cameraPosition);
		camera->SetLookFrame(glm::mat4(1.0f)); //Reset Look Frame
	}
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
	{
		glm::mat4 lookframe(1.0f);
		lookframe = glm::rotate(lookframe, glm::radians(90.0f), { 0, 1, 0 });
		glm::vec3 cameraPosition(30.0f, 5.0f, 0.0f);
		camera->SetPosition(cameraPosition);
		camera->SetLookFrame(lookframe); //Reset Look Frame
		
	}
	if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
	{
		glm::mat4 lookframe(1.0f);
		lookframe = glm::rotate(lookframe, glm::radians(180.0f), { 0, 1, 0 });
		glm::vec3 cameraPosition(0.0f, 5.0f, -30.0f);
		camera->SetPosition(cameraPosition);
		camera->SetLookFrame(lookframe); //Reset Look Frame
	}
	if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
	{
		glm::mat4 lookframe(1.0f);
		lookframe = glm::rotate(lookframe, glm::radians(-90.0f), { 0, 1, 0 });
		glm::vec3 cameraPosition(-30.0f, 5.0f, 0.0f);
		camera->SetPosition(cameraPosition);
		camera->SetLookFrame(lookframe); //Reset Look Frame
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

void GraphicsEnvironment::Run2D()
{
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

	glm::vec3 clearColor = { 0.2f, 0.3f, 0.3f };

	float angle = 0, childAngle = 0;
	float cameraX = -10, cameraY = 0;
	glm::mat4 view;

	//Lab 5 Part 1
	ImGuiIO& io = ImGui::GetIO();

	//Render Loop
	while (!glfwWindowShouldClose(window)) {
		//ProcessInput(window); Needs timer 

		glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		view = CreateViewMatrix(
			glm::vec3(cameraX, cameraY, 1.0f),
			glm::vec3(0.0f, 0.0f, -1.0f),
			glm::vec3(0.0f, 1.0f, 0.0f)
		);

		//Lab 5
		GetRenderer("renderer")->SetView(view);
		GetRenderer("renderer")->SetProjection(projection);
		GetRenderer("renderer")->RenderScene(*camera);

		GetRenderer("textureRenderer")->SetView(view);
		GetRenderer("textureRenderer")->SetProjection(projection);
		GetRenderer("textureRenderer")->RenderScene(*camera);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("Computing Interactive Graphics");
		ImGui::Text(GetRenderer("renderer")->GetShader()->GetLog().c_str()); //Needed?
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
	return; //Change int to void return type
}

void GraphicsEnvironment::Run3D()
{
	float cubeYAngle = 0;
	float cubeXAngle = 0;
	float cubeZAngle = 0;
	float left = -20.0f;
	float right = 20.0f;
	float bottom = -20.0f;
	float top = 20.0f;
	int width, height;

	//std::string message = result.message;

	float aspectRatio;
	float nearPlane = 1.0f;
	float farPlane = 50.0f;
	float fieldOfView = 60;

	//Lab 6 Part 3
	glm::vec3 cameraPosition(0.0f, 5.0f, 30.0f);
	camera->SetPosition(cameraPosition);
	glm::vec3 cameraTarget(0.0f, 0.0f, 0.0f);
	//glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);

	glm::mat4 view = camera->LookForward(); //Lab7 set default view
	glm::mat4 projection;
	glm::mat4 referenceFrame(1.0f);
	glm::vec3 clearColor = { 0.2f, 0.3f, 0.3f };

	//Lab 5 Part 1
	ImGuiIO& io = ImGui::GetIO();

	//Lab 6
	Timer timer;
	double elapsedSeconds;

	//Lab 6 Part 2.5 Animation
	std::shared_ptr<RotateAnimation> rotateAnimation = std::make_shared<RotateAnimation>();
	rotateAnimation->SetObject(objectManager->GetObject("Crate"));
	objectManager->GetObject("Crate")->SetAnimation(rotateAnimation);

	//Lab 7 
	bool correctGamma = false;

	//Lab 8 
	Ray ray;
	GeometricPlane plane;
	Intersection intersection;

	while (!glfwWindowShouldClose(window)) {

		elapsedSeconds = timer.GetElapsedTimeInSeconds();

		ProcessInput(window, elapsedSeconds, view);
		glfwGetWindowSize(window, &width, &height);

		//Lab 6 Part 4 
		mouse.windowWidth = width;
		mouse.windowHeight = height;

		if (correctGamma)
		{
			glEnable(GL_FRAMEBUFFER_SRGB);
		}
		else
		{
			glDisable(GL_FRAMEBUFFER_SRGB);
		}

		glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		//referenceFrame = glm::rotate(glm::mat4(1.0f), glm::radians(cubeYAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		//referenceFrame = glm::rotate(referenceFrame, glm::radians(cubeXAngle), glm::vec3(1.0f, 0.0f, 0.0f));
		//referenceFrame = glm::rotate(referenceFrame, glm::radians(cubeZAngle), glm::vec3(0.0f, 0.0f, 1.0f));

		//Lab 7
		if (camera->LookWithMouse())
		{
			camera->SetLookFrame(mouse.spherical.ToMat4());
		}
		view = camera->LookForward();
		
		//Set Local Light Position 
		objectManager->GetObject("Lightbulb")->SetPosition(GetRenderer("renderer")->GetScene()->GetLocalLight().position);
		objectManager->GetObject("Lightbulb")->PointAt(camera->GetPosition());

		if (width >= height) {
			aspectRatio = width / (height * 1.0f);
		}
		else {
			aspectRatio = height / (width * 1.0f);
		}
		projection = glm::perspective(
			glm::radians(fieldOfView), aspectRatio, nearPlane, farPlane);

		objectManager->Update(elapsedSeconds);

		//Create a plane using the y value of the floor 
		plane.SetDistanceFromOrigin(objectManager->GetObject("Plane")->GetReferenceFrame()[3].y);
		//Get the mosue ray 
		ray = GetMouseRay(projection, view);
		//If mouse ray intersects if floor plane position the cylinder there 
		intersection = ray.GetIntersectionWithPlane(plane);

		if (intersection.isIntersecting) {
			objectManager->GetObject("cylinder")->SetPosition(glm::vec3{ intersection.point.x, 4.0f, intersection.point.z });
		}

		//Lab 9 If the mouse ray intersectes with either the textured cube or the crate then 
		//set their material ambient intensity to 1
		auto cuboid = objectManager->GetObject("Cuboid");
		if (cuboid->IsIntersectingWithRay(ray))
		{
			cuboid->SetAmbientIntensity(1.0f);
		}
		else
		{
			cuboid->SetAmbientIntensity(0.1f);
		}
		auto crate = objectManager->GetObject("Crate");
		if (crate->IsIntersectingWithRay(ray))
		{
			crate->SetAmbientIntensity(1.0f);
		}
		else
		{
			crate->SetAmbientIntensity(0.1f);
		}

		// Render the scene (cuboid, crate, floor) 
		GetRenderer("renderer")->SetView(view);
		GetRenderer("renderer")->SetProjection(projection);
		GetRenderer("renderer")->RenderScene(*camera);

		//Lab 7 Render the lightbulb 
		GetRenderer("lightbulbrenderer")->SetView(view);
		GetRenderer("lightbulbrenderer")->SetProjection(projection);
		GetRenderer("lightbulbrenderer")->RenderScene(*camera);

		//Lab 8 Render the PC Objects
		GetRenderer("pcobjectrenderer")->SetView(view);
		GetRenderer("pcobjectrenderer")->SetProjection(projection);
		GetRenderer("pcobjectrenderer")->RenderScene(*camera);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::Begin("Computing Interactive Graphics");
		ImGui::Text(GetRenderer("renderer")->GetShader()->GetLog().c_str()); 
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
			1000.0f / io.Framerate, io.Framerate);
		ImGui::Text("Elapsed seconds: %.3f", elapsedSeconds); //Lab 6
		ImGui::ColorEdit3("Background color", (float*)&clearColor.r);
		ImGui::SliderFloat("X Angle", &cubeXAngle, 0, 360);
		ImGui::SliderFloat("Y Angle", &cubeYAngle, 0, 360);
		ImGui::SliderFloat("Z Angle", &cubeZAngle, 0, 360);
		ImGui::SliderFloat("Global Intensity", &GetRenderer("renderer")->GetScene()->GetGlobalLight().intensity, 0, 1);
		ImGui::SliderFloat("Local Intensity", &GetRenderer("renderer")->GetScene()->GetLocalLight().intensity, 0, 1);
		ImGui::Checkbox("Correct gamma", &correctGamma);
		ImGui::DragFloat3("Set Local Light Position", &GetRenderer("renderer")->GetScene()->GetLocalLight().position.x);
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

void GraphicsEnvironment::OnMouseMove(GLFWwindow* window, double mouseX, double mouseY)
{
	self->mouse.x = mouseX;
	self->mouse.y = mouseY;

	float xPercent = static_cast<float>(self->mouse.x / self->mouse.windowWidth);
	float yPercent = static_cast<float>(self->mouse.y / self->mouse.windowHeight);

	self->mouse.spherical.theta = 90.0f - (xPercent * 180); // left/right
	self->mouse.spherical.phi = 180.0f - (yPercent * 180); // up/down

	self->mouse.nsx = xPercent * 2.0 - 1.0;
	self->mouse.nsy = -(yPercent * 2.0 - 1.0);
}

Ray GraphicsEnvironment::GetMouseRay(const glm::mat4& projection, const glm::mat4& view)
{
	Ray ray;
	ray.Create(self->mouse.nsx, self->mouse.nsy, projection, view);
	return ray;
}

