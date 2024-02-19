#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture()
{
	textureData = nullptr;
	isLoadedFromFile = false;
	glGenTextures(1, &textureID);
	type = GL_TEXTURE_2D;
	width = 0;
	height = 0;
	internalFormat = GL_RGBA8;
	sourceFormat = GL_RGBA;
	wrapS = GL_REPEAT;
	wrapT = GL_REPEAT; 
	magFilter = GL_NEAREST;
	minFilter = GL_NEAREST; 
	numberOfChannels = 4;
}

Texture::~Texture()
{
	Cleanup();
	glDeleteTextures(1, &textureID);
}

void Texture::setWidth(unsigned int width)
{
	this->width = width;
}

void Texture::setHeight(unsigned int height) 
{
	this->height = height; 
}

void Texture::setTextureData(unsigned int count, unsigned char* data)
{
	Cleanup();
	textureData = new unsigned char[count];
	memcpy(textureData, data, count);
	isLoadedFromFile = false; 
}

void Texture::SelectToChange()
{
	glBindTexture(type, textureID);
}

void Texture::Deselect()
{
	glBindTexture(type, 0);
}

void Texture::SelectToRender(int textureUnit = 0)
{
	glActiveTexture(GL_TEXTURE0 + textureUnit);
	glBindTexture(type, textureID);
}

void Texture::Allocate()
{
	SelectToChange();
	// Apply texture parameters
	glTexParameteri(type, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(type, GL_TEXTURE_WRAP_T, wrapT);
	glTexParameteri(type, GL_TEXTURE_MAG_FILTER, magFilter);
	glTexParameteri(type, GL_TEXTURE_MIN_FILTER, minFilter);
	//Send Texture Data To GPU
	glTexImage2D(type, 0, internalFormat, width, height, 0, sourceFormat, GL_UNSIGNED_BYTE, textureData);
	Cleanup();
	//Generate mipmaps 
	glGenerateMipmap(type);
	Deselect();
}

void Texture::LoadTextureDataFromFile(const std::string& filepath)
{
	Cleanup();
	int width, height;
	stbi_set_flip_vertically_on_load(true);
	textureData = stbi_load(filepath.c_str(), &width, &height, &numberOfChannels, 0);
	this->width = width;
	this->height = height;
	if (numberOfChannels == 3)
	{
		sourceFormat = GL_RGB;
	}
	isLoadedFromFile = true; 
}

void Texture::Cleanup()
{
	if (textureData == nullptr)
	{
		return;
	}
	if (isLoadedFromFile == false)
	{
		delete[] textureData;
	}
	if (isLoadedFromFile == true)
	{
		stbi_image_free(textureData);
	}
	textureData = nullptr;
}
