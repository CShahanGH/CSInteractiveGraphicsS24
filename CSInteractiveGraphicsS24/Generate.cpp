#include "Generate.h"

Generate::Generate()
{
}

Generate::~Generate()
{

}

std::shared_ptr<VertexBuffer> Generate::Cuboid(float width, float height, float depth, glm::vec3 color, glm::vec2 tex)
{
	std::shared_ptr<VertexBuffer> buffer = std::make_shared<VertexBuffer>(8);

	float halfwidth = width / 2;
	float halfheight = height / 2;
	float halfdepth = depth / 2; 

	/*
	//Front Face
	buffer->AddVertexData(8, -5.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f); //A
	buffer->AddVertexData(8, -5.0f, -5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f); //B
	buffer->AddVertexData(8, 5.0f, -5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f); //C
	buffer->AddVertexData(8, -5.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f); //A
	buffer->AddVertexData(8, 5.0f, -5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f); //C
	buffer->AddVertexData(8, 5.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f); //D

	//Right Face
	buffer->AddVertexData(8, 5.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f); //E
	buffer->AddVertexData(8, 5.0f, -5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f); //F
	buffer->AddVertexData(8, 5.0f, -5.0f, -5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f); //G
	buffer->AddVertexData(8, 5.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f); //E
	buffer->AddVertexData(8, 5.0f, -5.0f, -5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f); //G
	buffer->AddVertexData(8, 5.0f, 5.0f, -5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f); //H

	//Back Face
	buffer->AddVertexData(8, 5.0f, 5.0f, -5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f); //I
	buffer->AddVertexData(8, 5.0f, -5.0f, -5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f); //J
	buffer->AddVertexData(8, -5.0f, -5.0f, -5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f); //K
	buffer->AddVertexData(8, 5.0f, 5.0f, -5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f);  //I
	buffer->AddVertexData(8, -5.0f, -5.0f, -5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f); //K
	buffer->AddVertexData(8, -5.0f, 5.0f, -5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f); //L

	//Left Face
	buffer->AddVertexData(8, -5.0f, 5.0f, -5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f); //M
	buffer->AddVertexData(8, -5.0f, -5.0f, -5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f); //N
	buffer->AddVertexData(8, -5.0f, -5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f); //O
	buffer->AddVertexData(8, -5.0f, 5.0f, -5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f); //M
	buffer->AddVertexData(8, -5.0f, -5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f); //O
	buffer->AddVertexData(8, -5.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f); //P

	//Top Face
	buffer->AddVertexData(8, -5.0f, 5.0f, -5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f); //Q
	buffer->AddVertexData(8, -5.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f); //R
	buffer->AddVertexData(8, 5.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f); //S
	buffer->AddVertexData(8, -5.0f, 5.0f, -5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f); //Q
	buffer->AddVertexData(8, 5.0f, 5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f); //S
	buffer->AddVertexData(8, 5.0f, 5.0f, -5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f); //T

	//Bottom Face
	buffer->AddVertexData(8, 5.0f, -5.0f, -5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f); //U,
	buffer->AddVertexData(8, 5.0f, -5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f); //V
	buffer->AddVertexData(8, -5.0f, -5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f); //W
	buffer->AddVertexData(8, 5.0f, -5.0f, -5.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f); //U
	buffer->AddVertexData(8, -5.0f, -5.0f, 5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f); //W
	buffer->AddVertexData(8, -5.0f, -5.0f, -5.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f); //X
	*/

	//Front Face
	buffer->AddVertexData(8, -halfwidth, halfheight , halfdepth, color.r, color.g, color.b, 0, tex.t); //A
	buffer->AddVertexData(8, -halfwidth , -halfheight, halfdepth, color.r, color.g, color.b, 0,0); //B
	buffer->AddVertexData(8, halfwidth, -halfheight, halfdepth, color.r, color.g, color.b, tex.s, 0); //C
	buffer->AddVertexData(8, -halfwidth, halfheight, halfdepth, color.r, color.g, color.b, 0, tex.t); //A
	buffer->AddVertexData(8, halfwidth, -halfheight, halfdepth, color.r, color.g, color.b, tex.s, 0); //C
	buffer->AddVertexData(8, halfwidth, halfheight, halfdepth, color.r, color.g, color.b, tex.s, tex.t); //D

	//Right Face
	buffer->AddVertexData(8, halfwidth, halfheight, halfdepth,   color.r, color.g, color.b, 0, tex.t); //E
	buffer->AddVertexData(8, halfwidth, -halfheight, halfdepth,  color.r, color.g, color.b, 0, 0); //F
	buffer->AddVertexData(8, halfwidth, -halfheight, -halfdepth, color.r, color.g, color.b, tex.s, 0); //G
	buffer->AddVertexData(8, halfwidth, halfheight, halfdepth,   color.r, color.g, color.b, 0, tex.t); //E
	buffer->AddVertexData(8, halfwidth, -halfheight, -halfdepth, color.r, color.g, color.b, tex.s, 0); //G
	buffer->AddVertexData(8, halfwidth, halfheight, -halfdepth,  color.r, color.g, color.b, tex.s, tex.t); //H

	//Back Face
	buffer->AddVertexData(8, halfwidth, halfheight, -halfdepth,   color.r, color.g, color.b, 0, tex.t); //I
	buffer->AddVertexData(8, halfwidth, -halfheight, -halfdepth,  color.r, color.g, color.b, 0, 0); //J
	buffer->AddVertexData(8, -halfwidth, -halfheight, -halfdepth, color.r, color.g, color.b, tex.s, 0); //K
	buffer->AddVertexData(8, halfwidth, halfheight, -halfdepth,   color.r, color.g, color.b, 0, tex.t);  //I
	buffer->AddVertexData(8, -halfwidth, -halfheight, -halfdepth, color.r, color.g, color.b, tex.s, 0); //K
	buffer->AddVertexData(8, -halfwidth, halfheight, -halfdepth,  color.r, color.g, color.b, tex.s, tex.t); //L

	//Left Face
	buffer->AddVertexData(8, -halfwidth, halfheight, -halfdepth,  color.r, color.g, color.b, 0, tex.t); //M
	buffer->AddVertexData(8, -halfwidth, -halfheight, -halfdepth, color.r, color.g, color.b, 0, 0); //N
	buffer->AddVertexData(8, -halfwidth, -halfheight, halfdepth,  color.r, color.g, color.b, tex.s, 0); //O
	buffer->AddVertexData(8, -halfwidth, halfheight, -halfdepth,  color.r, color.g, color.b, 0, tex.t); //M
	buffer->AddVertexData(8, -halfwidth, -halfheight, halfdepth,  color.r, color.g, color.b, tex.s, 0); //O
	buffer->AddVertexData(8, -halfwidth, halfheight, halfdepth,   color.r, color.g, color.b, tex.s, tex.t); //P

	//Top Face
	buffer->AddVertexData(8, -halfwidth, halfheight, -halfdepth, color.r, color.g, color.b, 0, tex.t); //Q
	buffer->AddVertexData(8, -halfwidth, halfheight, halfdepth,  color.r, color.g, color.b, 0, 0); //R
	buffer->AddVertexData(8, halfwidth, halfheight, halfdepth,   color.r, color.g, color.b, tex.s, 0); //S
	buffer->AddVertexData(8, -halfwidth, halfheight, -halfdepth, color.r, color.g, color.b, 0, tex.t); //Q
	buffer->AddVertexData(8, halfwidth, halfheight, halfdepth,   color.r, color.g, color.b, tex.s, 0); //S
	buffer->AddVertexData(8, halfwidth, halfheight, -halfdepth,  color.r, color.g, color.b, tex.s, tex.t); //T

	//Bottom Face
	buffer->AddVertexData(8, halfwidth, -halfheight, -halfdepth,  color.r, color.g, color.b, 0, tex.t); //U, 
	buffer->AddVertexData(8, halfwidth, -halfheight, halfdepth,   color.r, color.g, color.b, 0, 0); //V
	buffer->AddVertexData(8, -halfwidth, -halfheight, halfdepth,  color.r, color.g, color.b, tex.s, 0); //W
	buffer->AddVertexData(8, halfwidth, -halfheight, -halfdepth,  color.r, color.g, color.b, 0, tex.t); //U
	buffer->AddVertexData(8, -halfwidth, -halfheight, halfdepth,  color.r, color.g, color.b, tex.s, 0); //W
	buffer->AddVertexData(8, -halfwidth, -halfheight, -halfdepth, color.r, color.g, color.b, tex.s, tex.t); //X

	return buffer;
}

std::shared_ptr<VertexBuffer> Generate::XZPlane(float width, float depth, glm::vec3 color, glm::vec2 tex)
{
	std::shared_ptr<VertexBuffer> buffer = std::make_shared<VertexBuffer>(8);

	//Top
	buffer->AddVertexData(8, -width, 0, -depth, color.r, color.g, color.b, 0, tex.t); 
	buffer->AddVertexData(8, -width, 0, depth, color.r, color.g, color.b, 0, 0); 
	buffer->AddVertexData(8, width, 0, depth, color.r, color.g, color.b, tex.s, 0); 
	buffer->AddVertexData(8, -width, 0, -depth, color.r, color.g, color.b, 0, tex.t); 
	buffer->AddVertexData(8, width, 0, depth, color.r, color.g, color.b, tex.s, 0); 
	buffer->AddVertexData(8, width, 0, -depth, color.r, color.g, color.b, tex.s, tex.t); 

	buffer->AddVertexData(8, width, 0, -depth, color.r, color.g, color.b, 0, tex.t);   
	buffer->AddVertexData(8, width, 0, depth, color.r, color.g, color.b,  0, 0); 
	buffer->AddVertexData(8, -width, 0, depth, color.r, color.g, color.b, tex.s, 0); 
	buffer->AddVertexData(8, width, 0, -depth, color.r, color.g, color.b, 0, tex.t); 
	buffer->AddVertexData(8, -width, 0, depth, color.r, color.g, color.b, tex.s, 0); 
	buffer->AddVertexData(8, -width, 0, -depth, color.r, color.g, color.b, tex.s, tex.t); 
	//Bottom

	return buffer;
}

std::shared_ptr<VertexBuffer> Generate::XYPlane(float width, float height, glm::vec3 color, glm::vec2 tex)
{
	std::shared_ptr<VertexBuffer> buffer = std::make_shared<VertexBuffer>(8);

	//Front Face
	buffer->AddVertexData(8, -width, height, 0, color.r, color.g, color.b, 0, tex.t); //A
	buffer->AddVertexData(8, -width, -height, 0, color.r, color.g, color.b, 0, 0); //B
	buffer->AddVertexData(8, width, -height, 0, color.r, color.g, color.b, tex.s, 0); //C
	buffer->AddVertexData(8, -width, height, 0, color.r, color.g, color.b, 0, tex.t); //A
	buffer->AddVertexData(8, width, -height, 0, color.r, color.g, color.b, tex.s, 0); //C
	buffer->AddVertexData(8, width, height, 0, color.r, color.g, color.b, tex.s, tex.t); //D

	//Back Face
	buffer->AddVertexData(8, width, height, 0, color.r, color.g, color.b, 0, tex.t); //I
	buffer->AddVertexData(8, width, -height, 0, color.r, color.g, color.b, 0, 0); //J
	buffer->AddVertexData(8, -width, -height, 0, color.r, color.g, color.b, tex.s, 0); //K
	buffer->AddVertexData(8, width, height, 0, color.r, color.g, color.b, 0, tex.t);  //I
	buffer->AddVertexData(8, -width, -height, 0, color.r, color.g, color.b, tex.s, 0); //K
	buffer->AddVertexData(8, -width, height, 0, color.r, color.g, color.b, tex.s, tex.t); //L

	return buffer;
}

//Lab 7
std::shared_ptr<VertexBuffer> Generate::CuboidWithNormals(float width, float height, float depth, glm::vec4 color, glm::vec3 normal, glm::vec2 tex)
{
	std::shared_ptr<VertexBuffer> buffer = std::make_shared<VertexBuffer>(12);

	float halfwidth = width / 2;
	float halfheight = height / 2;
	float halfdepth = depth / 2;

	glm::vec3 front = { 0, 0, 1 };
	glm::vec3 back = { 0, 0, -1 };
	glm::vec3 left = { -1, 0, 0 };
	glm::vec3 right = { 1, 0, 0 };
	glm::vec3 top = { 0, 1, 0 };
	glm::vec3 bottom = { 0, -1, 0 };
	
	//Front Face
	buffer->AddVertexData(12, -halfwidth, halfheight, halfdepth, color.r, color.g, color.b, color.a, front.x, front.y, front.z, 0, tex.t); 
	buffer->AddVertexData(12, -halfwidth, -halfheight, halfdepth, color.r, color.g, color.b, color.a, front.x, front.y, front.z, 0, 0);
	buffer->AddVertexData(12, halfwidth, -halfheight, halfdepth, color.r, color.g, color.b, color.a, front.x, front.y, front.z, tex.s, 0);
	buffer->AddVertexData(12, -halfwidth, halfheight, halfdepth, color.r, color.g, color.b, color.a, front.x, front.y, front.z, 0, tex.t);
	buffer->AddVertexData(12, halfwidth, -halfheight, halfdepth, color.r, color.g, color.b, color.a, front.x, front.y, front.z, tex.s, 0);
	buffer->AddVertexData(12, halfwidth, halfheight, halfdepth, color.r, color.g, color.b, color.a, front.x, front.y, front.z, tex.s, tex.t);

	//Right Face
	buffer->AddVertexData(12, halfwidth, halfheight, halfdepth, color.r, color.g, color.b, color.a, right.x, right.y, right.z, 0, tex.t); 
	buffer->AddVertexData(12, halfwidth, -halfheight, halfdepth, color.r, color.g, color.b, color.a, right.x, right.y, right.z, 0, 0);
	buffer->AddVertexData(12, halfwidth, -halfheight, -halfdepth, color.r, color.g, color.b, color.a, right.x, right.y, right.z, tex.s, 0);
	buffer->AddVertexData(12, halfwidth, halfheight, halfdepth, color.r, color.g, color.b, color.a, right.x, right.y, right.z, 0, tex.t);
	buffer->AddVertexData(12, halfwidth, -halfheight, -halfdepth, color.r, color.g, color.b, color.a, right.x, right.y, right.z, tex.s, 0);
	buffer->AddVertexData(12, halfwidth, halfheight, -halfdepth, color.r, color.g, color.b, color.a, right.x, right.y, right.z, tex.s, tex.t);

	//Back Face
	buffer->AddVertexData(12, halfwidth, halfheight, -halfdepth, color.r, color.g, color.b, color.a, back.x, back.y, back.z, 0, tex.t); 
	buffer->AddVertexData(12, halfwidth, -halfheight, -halfdepth, color.r, color.g, color.b, color.a, back.x, back.y, back.z, 0, 0);
	buffer->AddVertexData(12, -halfwidth, -halfheight, -halfdepth, color.r, color.g, color.b, color.a, back.x, back.y, back.z, tex.s, 0);
	buffer->AddVertexData(12, halfwidth, halfheight, -halfdepth, color.r, color.g, color.b, color.a, back.x, back.y, back.z, 0, tex.t);
	buffer->AddVertexData(12, -halfwidth, -halfheight, -halfdepth, color.r, color.g, color.b, color.a, back.x, back.y, back.z, tex.s, 0);
	buffer->AddVertexData(12, -halfwidth, halfheight, -halfdepth, color.r, color.g, color.b, color.a, back.x, back.y, back.z, tex.s, tex.t);

	//Left Face
	buffer->AddVertexData(12, -halfwidth, halfheight, -halfdepth, color.r, color.g, color.b, color.a, left.x, left.y, left.z, 0, tex.t); 
	buffer->AddVertexData(12, -halfwidth, -halfheight, -halfdepth, color.r, color.g, color.b, color.a, left.x, left.y, left.z, 0, 0);
	buffer->AddVertexData(12, -halfwidth, -halfheight, halfdepth, color.r, color.g, color.b, color.a, left.x, left.y, left.z, tex.s, 0);
	buffer->AddVertexData(12, -halfwidth, halfheight, -halfdepth, color.r, color.g, color.b, color.a, left.x, left.y, left.z, 0, tex.t);
	buffer->AddVertexData(12, -halfwidth, -halfheight, halfdepth, color.r, color.g, color.b, color.a, left.x, left.y, left.z, tex.s, 0);
	buffer->AddVertexData(12, -halfwidth, halfheight, halfdepth, color.r, color.g, color.b, color.a, left.x, left.y, left.z, tex.s, tex.t);

	//Top Face
	buffer->AddVertexData(12, -halfwidth, halfheight, -halfdepth, color.r, color.g, color.b, color.a, top.x, top.y, top.z, 0, tex.t);
	buffer->AddVertexData(12, -halfwidth, halfheight, halfdepth, color.r, color.g, color.b, color.a, top.x, top.y, top.z, 0, 0);
	buffer->AddVertexData(12, halfwidth, halfheight, halfdepth, color.r, color.g, color.b, color.a, top.x, top.y, top.z, tex.s, 0);
	buffer->AddVertexData(12, -halfwidth, halfheight, -halfdepth, color.r, color.g, color.b, color.a, top.x, top.y, top.z, 0, tex.t);
	buffer->AddVertexData(12, halfwidth, halfheight, halfdepth, color.r, color.g, color.b, color.a, top.x, top.y, top.z, tex.s, 0);
	buffer->AddVertexData(12, halfwidth, halfheight, -halfdepth, color.r, color.g, color.b, color.a, top.x, top.y, top.z, tex.s, tex.t);

	//Bottom Face
	buffer->AddVertexData(12, halfwidth, -halfheight, -halfdepth, color.r, color.g, color.b, color.a, bottom.x, bottom.y, bottom.z, 0, tex.t);  
	buffer->AddVertexData(12, halfwidth, -halfheight, halfdepth, color.r, color.g, color.b, color.a, bottom.x, bottom.y, bottom.z, 0, 0);
	buffer->AddVertexData(12, -halfwidth, -halfheight, halfdepth, color.r, color.g, color.b, color.a, bottom.x, bottom.y, bottom.z, tex.s, 0);
	buffer->AddVertexData(12, halfwidth, -halfheight, -halfdepth, color.r, color.g, color.b, color.a, bottom.x, bottom.y, bottom.z, 0, tex.t);
	buffer->AddVertexData(12, -halfwidth, -halfheight, halfdepth, color.r, color.g, color.b, color.a, bottom.x, bottom.y, bottom.z, tex.s, 0);
	buffer->AddVertexData(12, -halfwidth, -halfheight, -halfdepth, color.r, color.g, color.b, color.a, bottom.x, bottom.y, bottom.z, tex.s, tex.t);

	return buffer;
}

std::shared_ptr<VertexBuffer> Generate::XZPlaneWithNormals(float width, float depth, glm::vec4 color, glm::vec3 normal, glm::vec2 tex)
{
	std::shared_ptr<VertexBuffer> buffer = std::make_shared<VertexBuffer>(12);

	//Top
	buffer->AddVertexData(12, -width, 0, -depth, color.r, color.g, color.b, color.a, 0, 1, 0, 0, tex.t);
	buffer->AddVertexData(12, -width, 0, depth, color.r, color.g, color.b, color.a, 0, 1, 0, 0, 0);
	buffer->AddVertexData(12, width, 0, depth, color.r, color.g, color.b, color.a, 0, 1, 0, tex.s, 0);
	buffer->AddVertexData(12, -width, 0, -depth, color.r, color.g, color.b, color.a, 0, 1, 0, 0, tex.t);
	buffer->AddVertexData(12, width, 0, depth, color.r, color.g, color.b, color.a, 0, 1, 0, tex.s, 0);
	buffer->AddVertexData(12, width, 0, -depth, color.r, color.g, color.b, color.a, 0, 1, 0, tex.s, tex.t);

	//Bottom
	buffer->AddVertexData(12, width, 0, -depth, color.r, color.g, color.b, color.a, 0, -1, 0, 0, tex.t);
	buffer->AddVertexData(12, width, 0, depth, color.r, color.g, color.b, color.a, 0, -1, 0, 0, 0);
	buffer->AddVertexData(12, -width, 0, depth, color.r, color.g, color.b, color.a, 0, -1, 0, tex.s, 0);
	buffer->AddVertexData(12, width, 0, -depth, color.r, color.g, color.b, color.a, 0, -1, 0, 0, tex.t);
	buffer->AddVertexData(12, -width, 0, depth, color.r, color.g, color.b, color.a, 0, -1, 0, tex.s, 0);
	buffer->AddVertexData(12, -width, 0, -depth, color.r, color.g, color.b, color.a, 0, -1, 0, tex.s, tex.t);

	return buffer;
}
