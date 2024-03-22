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

//Lab 6 Part 1.6 
void SetUp3DScene1(std::shared_ptr<Shader>& shader, std::shared_ptr<Scene>& scene, GraphicsEnvironment& graphicsenvironment)
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
	std::shared_ptr<VertexBuffer> buffer = Generate::Cuboid(10.0f, 5.0f, 5.0f);

	/*
		A - 5.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
		B - 5.0f, -5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f
		C 5.0f, -5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f
		D 5.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f

		E 5.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
		F 5.0f, -5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f
		G 5.0f, -5.0f, -5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f
		H 5.0f, 5.0f, -5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f

		I 5.0f, 5.0f, -5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
		J 5.0f, -5.0f, -5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f
		K - 5.0f, -5.0f, -5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f
		L - 5.0f, 5.0f, -5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f

		M - 5.0f, 5.0f, -5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
		N - 5.0f, -5.0f, -5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f
		O - 5.0f, -5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f
		P - 5.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f

		Q - 5.0f, 5.0f, -5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
		R - 5.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f
		S 5.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f
		T 5.0f, 5.0f, -5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f

		U 5.0f, -5.0f, -5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
		V 5.0f, -5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f
		W - 5.0f, -5.0f, -5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f
		X - 5.0f, -5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f
	*/

	buffer->AddVertexAttribute("position", 0, 3, 0);
	buffer->AddVertexAttribute("color", 1, 3, 3);
	buffer->AddVertexAttribute("texCoord", 2, 2, 6);

	//Set the buffer's texture
	buffer->setTexture(texture);

	//Set the object's buffer
	cuboid->SetVertexBuffer(buffer);

	//Set the object's position
	cuboid->SetPosition(glm::vec3(0.0f, 2.501f, 0.0f));

	//Add object to the scene
	scene->AddObject(cuboid);

	graphicsenvironment.AddObject("Cuboid", cuboid);

	//Lab 5 Part 6
	std::shared_ptr<Texture> crateTex = std::make_shared<Texture>();
	std::shared_ptr<GraphicsObject> crateObj = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> crateBuffer = Generate::Cuboid(5.0f, 5.0f, 5.0f);

	crateTex->LoadTextureDataFromFile("Wooden Crate Texture.png");


	crateBuffer->AddVertexAttribute("position", 0, 3, 0);
	crateBuffer->AddVertexAttribute("color", 1, 3, 3);
	crateBuffer->AddVertexAttribute("texCoord", 2, 2, 6);

	crateBuffer->setTexture(crateTex);

	crateObj->SetVertexBuffer(crateBuffer);

	crateObj->SetPosition(glm::vec3(10.0f, 2.501f, -5.0f));

	scene->AddObject(crateObj);

	graphicsenvironment.AddObject("Crate", crateObj);

	//Lab 5 Part 7 adding a PLane 
	std::shared_ptr<Texture> planeTex = std::make_shared<Texture>();
	std::shared_ptr<GraphicsObject> plane = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> planeBuffer = Generate::XZPlane(15.0f, 15.0f);

	planeTex->LoadTextureDataFromFile("cobblestone_floor_08_diff_1k.jpg");

	planeBuffer->AddVertexAttribute("position", 0, 3, 0);
	planeBuffer->AddVertexAttribute("color", 1, 3, 3);
	planeBuffer->AddVertexAttribute("texCoord", 2, 2, 6);

	planeBuffer->setTexture(planeTex);

	plane->SetVertexBuffer(planeBuffer);

	plane->SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));

	scene->AddObject(plane);

	graphicsenvironment.AddObject("Plane", plane);
}

//Lab 7
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
	cuboid->SetPosition(glm::vec3(0.0f, 2.501f, 0.0f));

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

	scene->AddObject(crateObj);

	graphicsenvironment.AddObject("Crate", crateObj);

	//Lab 7 Adding Plane With Normals 
	
	std::shared_ptr<Texture> planeTex = std::make_shared<Texture>();
	std::shared_ptr<GraphicsObject> plane = std::make_shared<GraphicsObject>();
	std::shared_ptr<VertexBuffer> planeBuffer = Generate::XZPlaneWithNormals(15.0f, 15.0f);

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

//Lab 7 Part 3 

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

	//Lab 7 Adding Crate with Normals

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
	//Lab 6
	//SetUpScene1(shader, scene);
	//SetUp3DScene1(shader, scene, glfw);

	std::shared_ptr<Shader> textureShader;
	std::shared_ptr<Scene> textureScene;
	//SetUpTexturedScene(textureShader, textureScene);

	//Lab 7
	std::shared_ptr<Shader> shader2;
	std::shared_ptr<Scene> scene2;
	SetUp3DScene2(shader2, scene2, glfw);

	glfw.CreateRenderer("renderer", shader2);
	glfw.GetRenderer("renderer")->SetScene(scene2);
	
	//Lightbulb 
	std::shared_ptr<Shader> lightbulbshader;
	std::shared_ptr<Scene> lightbulbscene;
	SetUpLightBulb(lightbulbshader, lightbulbscene, glfw);
	glfw.CreateRenderer("lightbulbrenderer", lightbulbshader);
	glfw.GetRenderer("lightbulbrenderer")->SetScene(lightbulbscene);

	glfw.staticAllocate();

	glfw.Run3D();

}

