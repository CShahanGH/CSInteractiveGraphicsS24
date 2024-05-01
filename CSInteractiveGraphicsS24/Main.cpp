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
#include "Generate.h"
#include "HighlightBehavior.h"


//Used as reference for generating a 3D scene with normals from lab 7 
void SetUp3DScene2(std::shared_ptr<Shader>& shader, std::shared_ptr<Scene>& scene, GraphicsEnvironment& graphicsenvironment)
{
	//Read texture files and create a textureShader
	TextFile vertextFile("lighting.vert.glsl");
	TextFile fragmentFile("lighting.frag.glsl");
	std::string vertexSource = vertextFile.GetData();
	std::string fragmentSource = fragmentFile.GetData();
	shader = std::make_shared<Shader>(vertexSource, fragmentSource);

	//Add Unifroms
	shader->AddUniform("projection");
	shader->AddUniform("world");
	shader->AddUniform("view");
	shader->AddUniform("textUnit");
	shader->AddUniform("materialAmbientIntensity");
	shader->AddUniform("materialSpecularIntensity");
	shader->AddUniform("materialShininess");
	shader->AddUniform("globalLightPosition");
	shader->AddUniform("globalLightIntensity");
	shader->AddUniform("globalLightColor");
	shader->AddUniform("localLightPosition");
	shader->AddUniform("localLightColor");
	shader->AddUniform("localLightIntensity");
	shader->AddUniform("localLightAttenuationCoef");
	shader->AddUniform("viewPosition");

	std::shared_ptr<Texture> texture = std::make_shared<Texture>();

	texture->setHeight(4);
	texture->setWidth(4);

	// Create the texture data
	unsigned char* textureData = new unsigned char[] {
		0, 0, 0, 255, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 0, 255,
			0, 255, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 255, 0, 255,
			0, 255, 0, 255, 255, 255, 255, 255, 255, 255, 255, 255, 0, 255, 0, 255,
			0, 0, 0, 255, 255, 0, 0, 255, 255, 0, 0, 255, 0, 0, 0, 255
		};

	texture->setTextureData(64, textureData);

	//Shared scene object
	scene = std::make_shared<Scene>();

	//Shared graphics object 
	std::shared_ptr<GraphicsObject> cuboid = std::make_shared<GraphicsObject>();

	//Shared VertexBuffer
	std::shared_ptr<VertexBuffer> buffer = Generate::CuboidWithNormals(10.0f, 5.0f, 5.0f); // Lab 7 3.3?

	buffer->AddVertexAttribute("position", 0, 3, 0);
	buffer->AddVertexAttribute("vertexColor", 1, 4, 3);
	buffer->AddVertexAttribute("vertexNormal", 2, 3, 7);
	buffer->AddVertexAttribute("texCoord", 3, 2, 10);

	//Set the buffer's texture
	buffer->setTexture(texture);

	//Set the object's buffer
	cuboid->SetVertexBuffer(buffer);

	//Set the object's position
	cuboid->SetPosition(glm::vec3(0.0f, 2.50f, 0.0f));

	cuboid->CreateBoundingBox(10.0f, 5.0f, 5.0f); //Lab 9

	//Lab 10
	auto cuboidHighlight = std::make_shared<HighlightBehavior>();
	cuboidHighlight->SetObject(cuboid);

	cuboid->AddBehavior("highlight", cuboidHighlight);

	//Add object to the scene
	scene->AddObject(cuboid);

	graphicsenvironment.AddObject("Cuboid", cuboid);

	//Lab 7 Adding Crate with Normals

	std::shared_ptr<Texture> crateTex = std::make_shared<Texture>();
	std::shared_ptr<GraphicsObject> crateObj = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> crateBuffer = Generate::CuboidWithNormals(5.0f, 5.0f, 5.0f);

	crateTex->LoadTextureDataFromFile("Wooden Crate Texture.png");


	crateBuffer->AddVertexAttribute("position", 0, 3, 0);
	crateBuffer->AddVertexAttribute("color", 1, 4, 3);
	crateBuffer->AddVertexAttribute("vertexNormal", 2, 3, 7);
	crateBuffer->AddVertexAttribute("texCoord", 3, 2, 10);

	crateBuffer->setTexture(crateTex);

	crateObj->SetVertexBuffer(crateBuffer);

	crateObj->SetPosition(glm::vec3(10.0f, 2.501f, -5.0f));

	crateObj->CreateBoundingBox(5.0f, 5.0f, 5.0f);

	auto crateHighlight = std::make_shared<HighlightBehavior>();
	crateHighlight->SetObject(crateObj);

	crateObj->AddBehavior("highlight", crateHighlight);

	scene->AddObject(crateObj);

	graphicsenvironment.AddObject("Crate", crateObj);

	//Lab 10 Adding a textured cuboid in the south east corner of the plane 
	std::shared_ptr<Texture> Marble = std::make_shared<Texture>();
	std::shared_ptr<GraphicsObject> MarbleObj = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> MarbleBuffer = Generate::CuboidWithNormals(5.0f, 5.0f, 5.0f);

	Marble->LoadTextureDataFromFile("Marble.jpg");


	MarbleBuffer->AddVertexAttribute("position", 0, 3, 0);
	MarbleBuffer->AddVertexAttribute("color", 1, 4, 3);
	MarbleBuffer->AddVertexAttribute("vertexNormal", 2, 3, 7);
	MarbleBuffer->AddVertexAttribute("texCoord", 3, 2, 10);

	MarbleBuffer->setTexture(Marble);

	MarbleObj->SetVertexBuffer(MarbleBuffer);

	MarbleObj->SetPosition(glm::vec3(15.0f, 2.501f, 15.0f));

	MarbleObj->CreateBoundingBox(5.0f, 5.0f, 5.0f);

	auto MarbleHighlight = std::make_shared<HighlightBehavior>();
	MarbleHighlight->SetObject(MarbleObj);

	MarbleObj->AddBehavior("highlight", MarbleHighlight);

	scene->AddObject(MarbleObj);

	graphicsenvironment.AddObject("Marble", MarbleObj);


	//Lab 7 Adding Plane With Normals 
	
	std::shared_ptr<Texture> planeTex = std::make_shared<Texture>();
	std::shared_ptr<GraphicsObject> plane = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> planeBuffer = Generate::XZPlaneWithNormals(30.0f, 30.0f);

	planeTex->LoadTextureDataFromFile("cobblestone_floor_08_diff_1k.jpg");

	planeBuffer->AddVertexAttribute("position", 0, 3, 0);
	planeBuffer->AddVertexAttribute("color", 1, 4, 3);
	planeBuffer->AddVertexAttribute("vertexNormal", 2, 3, 7);
	planeBuffer->AddVertexAttribute("texCoord", 3, 2, 10);

	planeBuffer->setTexture(planeTex);

	plane->SetVertexBuffer(planeBuffer);

	plane->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

	scene->AddObject(plane);

	graphicsenvironment.AddObject("Plane", plane);
}

//Used as refernece for creating a textured object
void SetUpLightBulb(std::shared_ptr<Shader>& shader, std::shared_ptr<Scene>& scene, GraphicsEnvironment& graphicsenvironment)
{
	//Read texture files and create a textureShader
	TextFile vertextFile("texture.vert.glsl");
	TextFile fragmentFile("texture.frag.glsl");
	std::string vertexSource = vertextFile.GetData();
	std::string fragmentSource = fragmentFile.GetData();
	shader = std::make_shared<Shader>(vertexSource, fragmentSource);

	//Add Unifroms
	shader->AddUniform("projection");
	shader->AddUniform("world");
	shader->AddUniform("view");
	shader->AddUniform("textUnit");

	//Shared scene object
	scene = std::make_shared<Scene>();

	//Lab 7 Adding Lightbulb Object 

	std::shared_ptr<Texture> LightbulbTex = std::make_shared<Texture>();
	std::shared_ptr<GraphicsObject> LightbulbObj = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> LightbulbBuffer = Generate::XYPlane(1.0f, 1.0f);

	LightbulbTex->LoadTextureDataFromFile("lightbulb.png");


	LightbulbBuffer->AddVertexAttribute("position", 0, 3, 0);
	LightbulbBuffer->AddVertexAttribute("color", 1, 3, 3);
	LightbulbBuffer->AddVertexAttribute("texCoord", 2, 2, 6);

	LightbulbBuffer->setTexture(LightbulbTex);

	LightbulbObj->SetVertexBuffer(LightbulbBuffer);

	LightbulbObj->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

	scene->AddObject(LightbulbObj);

	graphicsenvironment.AddObject("Lightbulb", LightbulbObj);
}

//Level 1 Scene 
/*
  The goal of level 1 is to touch the red cube
  The player starts on the blue cube
  The method SetUpLevel1Scene scene generates a 3d scene of planes and cubes used in the 1st level
*/
void SetUpLevel1Scene(std::shared_ptr<Shader>& shader, std::shared_ptr<Scene>& scene, GraphicsEnvironment& graphicsenvironment)
{
	//Read texture files and create a textureShader
	TextFile vertextFile("lighting.vert.glsl");
	TextFile fragmentFile("lighting.frag.glsl");
	std::string vertexSource = vertextFile.GetData();
	std::string fragmentSource = fragmentFile.GetData();
	shader = std::make_shared<Shader>(vertexSource, fragmentSource);

	//Add Unifroms
	shader->AddUniform("projection");
	shader->AddUniform("world");
	shader->AddUniform("view");
	shader->AddUniform("textUnit");
	shader->AddUniform("materialAmbientIntensity");
	shader->AddUniform("materialSpecularIntensity");
	shader->AddUniform("materialShininess");
	shader->AddUniform("globalLightPosition");
	shader->AddUniform("globalLightIntensity");
	shader->AddUniform("globalLightColor");
	shader->AddUniform("localLightPosition");
	shader->AddUniform("localLightColor");
	shader->AddUniform("localLightIntensity");
	shader->AddUniform("localLightAttenuationCoef");
	shader->AddUniform("viewPosition");

	//Shared scene object
	scene = std::make_shared<Scene>();

	//Adding a plane with normals for the starting floor 
	std::shared_ptr<Texture> floorTex = std::make_shared<Texture>();
	std::shared_ptr<GraphicsObject> plane = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> planeBuffer = Generate::XZPlaneWithNormals(30.0f, 30.0f);

	floorTex->LoadTextureDataFromFile("cobblestone_floor_08_diff_1k.jpg");

	planeBuffer->AddVertexAttribute("position", 0, 3, 0);
	planeBuffer->AddVertexAttribute("color", 1, 4, 3);
	planeBuffer->AddVertexAttribute("vertexNormal", 2, 3, 7);
	planeBuffer->AddVertexAttribute("texCoord", 3, 2, 10);

	planeBuffer->setTexture(floorTex);

	plane->SetVertexBuffer(planeBuffer);

	plane->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

	plane->CreateBoundingBox(60.0f, 0.0f, 60.0f);

	scene->AddObject(plane);

	graphicsenvironment.AddObject("plane", plane);

	//First Crate Object
	std::shared_ptr<Texture> crateTex = std::make_shared<Texture>();
	std::shared_ptr<GraphicsObject> crateObj = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> crateBuffer = Generate::CuboidWithNormals(5.0f, 5.0f, 5.0f);

	crateTex->LoadTextureDataFromFile("Wooden Crate Texture.png");


	crateBuffer->AddVertexAttribute("position", 0, 3, 0);
	crateBuffer->AddVertexAttribute("color", 1, 4, 3);
	crateBuffer->AddVertexAttribute("vertexNormal", 2, 3, 7);
	crateBuffer->AddVertexAttribute("texCoord", 3, 2, 10);

	crateBuffer->setTexture(crateTex);

	crateObj->SetVertexBuffer(crateBuffer);

	crateObj->SetPosition(glm::vec3(10.0f, 2.501f, -5.0f));

	crateObj->CreateBoundingBox(5.0f, 5.0f, 5.0f);

	scene->AddObject(crateObj);

	graphicsenvironment.AddObject("Crate", crateObj);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	//Lab 5
	GraphicsEnvironment glfw;

	glfw.Init(4, 3);

	bool created = glfw.SetWindow(1920, 1080, "ETSU Computing Interactive Graphics");
	if (created == false) return -1;

	bool loaded = glfw.InitGlad();
	if (loaded == false) return -1;

	glfw.SetupGraphics();

	//Level 1
	std::shared_ptr<Shader> level1shader;
	std::shared_ptr<Scene> level1scene;
	SetUpLevel1Scene(level1shader, level1scene, glfw);

	glfw.CreateRenderer("level1renderer", level1shader);
	glfw.GetRenderer("level1renderer")->SetScene(level1scene);
	
	//Lightbulb 
	std::shared_ptr<Shader> lightbulbshader;
	std::shared_ptr<Scene> lightbulbscene;
	SetUpLightBulb(lightbulbshader, lightbulbscene, glfw);
	glfw.CreateRenderer("lightbulbrenderer", lightbulbshader);
	glfw.GetRenderer("lightbulbrenderer")->SetScene(lightbulbscene);

	glfw.staticAllocate();

	glfw.Run3D();
}

