#pragma once
#include "BaseObject.h"
#include <glad/glad.h>

class Texture : public BaseObject
{
private:
	unsigned char* textureData;
	bool isLoadedFromFile;
	unsigned int textureID, type, width, height, internalFormat, sourceFormat, wrapS, wrapT, magFilter, minFilter;

public:
	Texture();
	~Texture();

	inline unsigned char* GetTextureData() const { return textureData; }
	inline bool IsLoadedFromFile() const { return isLoadedFromFile; }
	inline unsigned int GetTextureID() const { return textureID; }

	void setWidth(unsigned int width);
	void setHeight(unsigned int height); 

	void setTextureData(unsigned int count, unsigned char* data);
	void SelectToChange();
	void Deselect();
	void SelectToRender(int textureUnit);
	void Allocate();

private: 
	void Cleanup();
};

