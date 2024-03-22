#include "Renderer.h"
#include "glm/glm.hpp";

Renderer::Renderer(std::shared_ptr<Shader>& shader)
{
	this->shader = shader;
	glGenVertexArrays(1, &this->vaoID);
}

void Renderer::AllocateVertexBuffers(const std::vector<std::shared_ptr<GraphicsObject>>& objects)
{
	glBindVertexArray(this->vaoID);
	for (auto & object : objects)
	{
		object->StaticAllocateVertexBuffer();
	}
	glBindVertexArray(0);
}

void Renderer::RenderScene(const Camera& camera)
{
	if (this->shader->IsCreated()) {
		glUseProgram(this->shader->GetShaderProgram());
		glBindVertexArray(this->vaoID);
		shader->SendMat4Uniform("view", view);
		shader->SendMat4Uniform("projection", projection); //lab5 part 2
		//Lab 7
		shader->SendVec3Uniform("globalLightPosition", scene->GetGlobalLight().position);
		shader->SendFloatUniform("globalLightIntensity", scene->GetGlobalLight().intensity);
		shader->SendVec3Uniform("globalLightColor", scene->GetGlobalLight().color);
		shader->SendVec3Uniform("localLightPosition", scene->GetLocalLight().position);
		shader->SendVec3Uniform("localLightColor", scene->GetLocalLight().color);
		shader->SendFloatUniform("localLightIntensity", scene->GetLocalLight().intensity);
		shader->SendFloatUniform("localLightAttenuationCoef", scene->GetLocalLight().attenuationCoef);
		shader->SendVec3Uniform("viewPosition", camera.GetPosition()); //const breaks 
		// Render the objects in the scene
		for (auto& object : scene->GetObjects()) {
			RenderObject(*object);
		}
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glUseProgram(0);
		glBindVertexArray(0);
	}
}

void Renderer::RenderObject(GraphicsObject& object)
{
	shader->SendMat4Uniform("world", object.GetReferenceFrame());
	auto& buffer = object.GetVertexBuffer();
	buffer->Select();

	//Lab 4
	if (buffer->HasTexture())
	{
		shader->SendIntUniform("texUnit", buffer->GetTextureUnit());
		buffer->GetTexture()->SelectToRender(buffer->GetTextureUnit());
	}

	shader->SendFloatUniform("materialAmbientIntesnsity", object.GetMaterial().ambientIntensity);
	shader->SendFloatUniform("materialSpecularIntensity", object.GetMaterial().specularIntensity);
	shader->SendFloatUniform("materialShininess", object.GetMaterial().shininess);

	buffer->SetUpAttributeInterpretration();
	glDrawArrays(buffer->GetPrimitiveType(), 0, buffer->GetNumberOfVertices());

	// Recursively render the children
	auto& children = object.GetChildren();
	for (auto& child : children) {
		RenderObject(*child);
	}
}



