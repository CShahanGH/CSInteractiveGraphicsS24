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


//Sets up a textured cube of a trophy
void SetUpTrophy(std::shared_ptr<Shader>& shader, std::shared_ptr<Scene>& scene, GraphicsEnvironment& graphicsenvironment)
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

	std::shared_ptr<Texture> TrophyTex = std::make_shared<Texture>();
	std::shared_ptr<GraphicsObject> TrophyObj = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> TrophyBuffer = Generate::XYPlane(1.0f, 1.0f);

	TrophyTex->LoadTextureDataFromFile("Trophy-Icon.png");


	TrophyBuffer->AddVertexAttribute("position", 0, 3, 0);
	TrophyBuffer->AddVertexAttribute("color", 1, 3, 3);
	TrophyBuffer->AddVertexAttribute("texCoord", 2, 2, 6);

	TrophyBuffer->setTexture(TrophyTex);

	TrophyObj->SetVertexBuffer(TrophyBuffer);

	TrophyObj->SetPosition(glm::vec3(0.0f, 60.0f, 0.0f));

	TrophyObj->CreateBoundingBox(5, 10, 5);

	scene->AddObject(TrophyObj);

	graphicsenvironment.AddObject("Trophy", TrophyObj);
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

	//Test Crate Object
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

	//cloud texture
	std::shared_ptr<Texture> cloudTex = std::make_shared<Texture>();
	cloudTex->LoadTextureDataFromFile("cloud.jpg");

	//x-axis cloud buffer
	std::shared_ptr<VertexBuffer> xCloudBuffer = Generate::CuboidWithNormals(10.0f, 2.0f, 5.0f);
	xCloudBuffer->AddVertexAttribute("position", 0, 3, 0);
	xCloudBuffer->AddVertexAttribute("color", 1, 4, 3);
	xCloudBuffer->AddVertexAttribute("vertexNormal", 2, 3, 7);
	xCloudBuffer->AddVertexAttribute("texCoord", 3, 2, 10);

	xCloudBuffer->setTexture(cloudTex);

	//z-axis cloud buffer
	std::shared_ptr<VertexBuffer> zCloudBuffer = Generate::CuboidWithNormals(5.0f, 2.0f, 10.0f);
	zCloudBuffer->AddVertexAttribute("position", 0, 3, 0);
	zCloudBuffer->AddVertexAttribute("color", 1, 4, 3);
	zCloudBuffer->AddVertexAttribute("vertexNormal", 2, 3, 7);
	zCloudBuffer->AddVertexAttribute("texCoord", 3, 2, 10);

	zCloudBuffer->setTexture(cloudTex);

	//North
	//First platform cloud
	std::shared_ptr<GraphicsObject> cloudObj1 = std::make_shared<GraphicsObject>();
	cloudObj1->SetVertexBuffer(xCloudBuffer);
	cloudObj1->SetPosition(glm::vec3(-5.0f, 2.50f, -35.0f));
	cloudObj1->CreateBoundingBox(10.0f, 2.0f, 5.0f);
	scene->AddObject(cloudObj1);
	graphicsenvironment.AddObject("Cloud1", cloudObj1);
	//Second platform cloud
	std::shared_ptr<GraphicsObject> cloudObj2 = std::make_shared<GraphicsObject>();
	cloudObj2->SetVertexBuffer(xCloudBuffer);
	cloudObj2->SetPosition(glm::vec3(5.0f, 10.0f, -45.0f));
	cloudObj2->CreateBoundingBox(10.0f, 2.0f, 5.0f);
	scene->AddObject(cloudObj2);
	graphicsenvironment.AddObject("Cloud2", cloudObj2);

	//Third platform cloud
	std::shared_ptr<GraphicsObject> cloudObj3 = std::make_shared<GraphicsObject>();
	cloudObj3->SetVertexBuffer(xCloudBuffer);
	cloudObj3->SetPosition(glm::vec3(10.0f, 15.0f, -40.0f));
	cloudObj3->CreateBoundingBox(10.0f, 2.0f, 5.0f);
	scene->AddObject(cloudObj3);
	graphicsenvironment.AddObject("Cloud3", cloudObj3);

	//Fourth platform cloud
	std::shared_ptr<GraphicsObject> cloudObj4 = std::make_shared<GraphicsObject>();
	cloudObj4->SetVertexBuffer(xCloudBuffer);
	cloudObj4->SetPosition(glm::vec3(20.0f, 5.0f, -55.0f));
	cloudObj4->CreateBoundingBox(10.0f, 2.0f, 5.0f);
	scene->AddObject(cloudObj4);
	graphicsenvironment.AddObject("Cloud4", cloudObj4);

	//Fifth platform cloud
	std::shared_ptr<GraphicsObject> cloudObj5 = std::make_shared<GraphicsObject>();
	cloudObj5->SetVertexBuffer(xCloudBuffer);
	cloudObj5->SetPosition(glm::vec3(30.0f, 10.0f, -50.0f));
	cloudObj5->CreateBoundingBox(10.0f, 2.0f, 5.0f);
	scene->AddObject(cloudObj5);
	graphicsenvironment.AddObject("Cloud5", cloudObj5);

	//East
	//Sixth platform cloud
	std::shared_ptr<GraphicsObject> cloudObj6 = std::make_shared<GraphicsObject>();
	cloudObj6->SetVertexBuffer(zCloudBuffer);
	cloudObj6->SetPosition(glm::vec3(40.0f, 15.0f, -35.0f));
	cloudObj6->CreateBoundingBox(5.0f, 2.0f, 10.0f);
	scene->AddObject(cloudObj6);
	graphicsenvironment.AddObject("Cloud6", cloudObj6);

	//Seventh platform cloud
	std::shared_ptr<GraphicsObject> cloudObj7 = std::make_shared<GraphicsObject>();
	cloudObj7->SetVertexBuffer(zCloudBuffer);
	cloudObj7->SetPosition(glm::vec3(45.0f, 5.0f, -15.0f));
	cloudObj7->CreateBoundingBox(5.0f, 2.0f, 10.0f);
	scene->AddObject(cloudObj7);
	graphicsenvironment.AddObject("Cloud7", cloudObj7);

	//Eight platform cloud
	std::shared_ptr<GraphicsObject> cloudObj8 = std::make_shared<GraphicsObject>();
	cloudObj8->SetVertexBuffer(zCloudBuffer);
	cloudObj8->SetPosition(glm::vec3(40.0f, 10.0f, -5.0f));
	cloudObj8->CreateBoundingBox(5.0f, 2.0f, 10.0f);
	scene->AddObject(cloudObj8);
	graphicsenvironment.AddObject("Cloud8", cloudObj8);

	//Ninth platform cloud
	std::shared_ptr<GraphicsObject> cloudObj9 = std::make_shared<GraphicsObject>();
	cloudObj9->SetVertexBuffer(zCloudBuffer);
	cloudObj9->SetPosition(glm::vec3(35.0f, 15.0f, 10.0f));
	cloudObj9->CreateBoundingBox(5.0f, 2.0f, 10.0f);
	scene->AddObject(cloudObj9);
	graphicsenvironment.AddObject("Cloud9", cloudObj9);

	//Tenth platform cloud
	std::shared_ptr<GraphicsObject> cloudObj10 = std::make_shared<GraphicsObject>();
	cloudObj10->SetVertexBuffer(zCloudBuffer);
	cloudObj10->SetPosition(glm::vec3(40.0f, 20.0f, 25.0f));
	cloudObj10->CreateBoundingBox(5.0f, 2.0f, 10.0f);
	scene->AddObject(cloudObj10);
	graphicsenvironment.AddObject("Cloud10", cloudObj10);

	//South
	//11 platform cloud
	std::shared_ptr<GraphicsObject> cloudObj11 = std::make_shared<GraphicsObject>();
	cloudObj11->SetVertexBuffer(xCloudBuffer);
	cloudObj11->SetPosition(glm::vec3(30.0f, 20.0f, 30.0f));
	cloudObj11->CreateBoundingBox(10.0f, 2.0f, 5.0f);
	scene->AddObject(cloudObj11);
	graphicsenvironment.AddObject("Cloud11", cloudObj11);

	//12 platform cloud
	std::shared_ptr<GraphicsObject> cloudObj12 = std::make_shared<GraphicsObject>();
	cloudObj12->SetVertexBuffer(xCloudBuffer);
	cloudObj12->SetPosition(glm::vec3(25.0f, 25.0f, 30.0f));
	cloudObj12->CreateBoundingBox(10.0f, 2.0f, 5.0f);
	scene->AddObject(cloudObj12);
	graphicsenvironment.AddObject("Cloud12", cloudObj12);

	//13 platform cloud 
	std::shared_ptr<GraphicsObject> cloudObj13 = std::make_shared<GraphicsObject>();
	cloudObj13->SetVertexBuffer(xCloudBuffer);
	cloudObj13->SetPosition(glm::vec3(15.0f, 25.0f, 35.0f));
	cloudObj13->CreateBoundingBox(10.0f, 2.0f, 5.0f);
	scene->AddObject(cloudObj13);
	graphicsenvironment.AddObject("Cloud13", cloudObj13);

	//14 platform cloud
	std::shared_ptr<GraphicsObject> cloudObj14 = std::make_shared<GraphicsObject>();
	cloudObj14->SetVertexBuffer(xCloudBuffer);
	cloudObj14->SetPosition(glm::vec3(0.0f, 30.0f, 30.0f));
	cloudObj14->CreateBoundingBox(10.0f, 2.0f, 5.0f);
	scene->AddObject(cloudObj14);
	graphicsenvironment.AddObject("Cloud14", cloudObj14);

	//15 platform cloud
	std::shared_ptr<GraphicsObject> cloudObj15 = std::make_shared<GraphicsObject>();
	cloudObj15->SetVertexBuffer(xCloudBuffer);
	cloudObj15->SetPosition(glm::vec3(-15.0f, 35.0f, 30.0f));
	cloudObj15->CreateBoundingBox(10.0f, 2.0f, 5.0f);
	scene->AddObject(cloudObj15);
	graphicsenvironment.AddObject("Cloud15", cloudObj15);

	//West
	//16 platform cloud
	std::shared_ptr<GraphicsObject> cloudObj16 = std::make_shared<GraphicsObject>();
	cloudObj16->SetVertexBuffer(zCloudBuffer);
	cloudObj16->SetPosition(glm::vec3(-20.0f, 40.0f, 20.0f));
	cloudObj16->CreateBoundingBox(10.0f, 2.0f, 5.0f);
	scene->AddObject(cloudObj16);
	graphicsenvironment.AddObject("Cloud16", cloudObj16);

	//17 platform cloud
	std::shared_ptr<GraphicsObject> cloudObj17 = std::make_shared<GraphicsObject>();
	cloudObj17->SetVertexBuffer(zCloudBuffer);
	cloudObj17->SetPosition(glm::vec3(-25.0f, 35.0f, 10.0f));
	cloudObj17->CreateBoundingBox(10.0f, 2.0f, 5.0f);
	scene->AddObject(cloudObj17);
	graphicsenvironment.AddObject("Cloud17", cloudObj17);

	//18 platform cloud
	std::shared_ptr<GraphicsObject> cloudObj18 = std::make_shared<GraphicsObject>();
	cloudObj18->SetVertexBuffer(zCloudBuffer);
	cloudObj18->SetPosition(glm::vec3(-30.0f, 40.0f, 0.0f));
	cloudObj18->CreateBoundingBox(10.0f, 2.0f, 5.0f);
	scene->AddObject(cloudObj18);
	graphicsenvironment.AddObject("Cloud18", cloudObj18);

	//19 platform cloud
	std::shared_ptr<GraphicsObject> cloudObj19 = std::make_shared<GraphicsObject>();
	cloudObj19->SetVertexBuffer(zCloudBuffer);
	cloudObj19->SetPosition(glm::vec3(-35.0f, 45.0f, -10.0f));
	cloudObj19->CreateBoundingBox(10.0f, 2.0f, 5.0f);
	scene->AddObject(cloudObj19);
	graphicsenvironment.AddObject("Cloud19", cloudObj19);

	//20 platform cloud
	std::shared_ptr<GraphicsObject> cloudObj20 = std::make_shared<GraphicsObject>();
	cloudObj20->SetVertexBuffer(zCloudBuffer);
	cloudObj20->SetPosition(glm::vec3(-25.0f, 50.0f, -15.0f));
	cloudObj20->CreateBoundingBox(10.0f, 2.0f, 5.0f);
	scene->AddObject(cloudObj20);
	graphicsenvironment.AddObject("Cloud20", cloudObj20);

	//Adding top platform 
	std::shared_ptr<GraphicsObject> topPlane = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> topPlaneBuffer = Generate::XZPlaneWithNormals(30.0f, 30.0f);

	topPlaneBuffer->AddVertexAttribute("position", 0, 3, 0);
	topPlaneBuffer->AddVertexAttribute("color", 1, 4, 3);
	topPlaneBuffer->AddVertexAttribute("vertexNormal", 2, 3, 7);
	topPlaneBuffer->AddVertexAttribute("texCoord", 3, 2, 10);

	topPlaneBuffer->setTexture(cloudTex);
	topPlane->SetVertexBuffer(topPlaneBuffer);
	topPlane->SetPosition(glm::vec3(0.0f, 60.0f, 0.0f));
	topPlane->CreateBoundingBox(60.0f, 0.0f, 60.0f);
	scene->AddObject(topPlane);
	graphicsenvironment.AddObject("topPlane", topPlane);
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
	std::shared_ptr<Shader> trophyshader;
	std::shared_ptr<Scene> trophyscene;
	SetUpTrophy(trophyshader, trophyscene, glfw);
	glfw.CreateRenderer("trophyrenderer", trophyshader);
	glfw.GetRenderer("trophyrenderer")->SetScene(trophyscene);

	glfw.staticAllocate();

	glfw.Run3D();
}

