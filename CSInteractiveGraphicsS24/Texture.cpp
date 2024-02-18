#include "Texture.h"

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

void Texture::Cleanup()
{
	if (textureData == nullptr)
	{
		return;
	}
	if (isLoadedFromFile = false)
	{
		delete[] textureData;
	}
	textureData = nullptr;
}
