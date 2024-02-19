#pragma once
#include "BaseObject.h"
#include <glad/glad.h>

class Texture : public BaseObject
{
private:
	unsigned char* textureData;
	bool isLoadedFromFile;
	unsigned int textureID, type, width, height, internalFormat, sourceFormat, wrapS, wrapT, magFilter, minFilter;
	int numberOfChannels; //lab 4 part 7

public:
	Texture();
	~Texture();

	inline unsigned char* GetTextureData() const { return textureData; }
	inline bool IsLoadedFromFile() const { return isLoadedFromFile; }
	inline unsigned int GetTextureID() const { return textureID; }
	inline unsigned int GetNumberOfChannels() const { return numberOfChannels; }


	void setWidth(unsigned int width);
	void setHeight(unsigned int height); 
	void setwrapS(unsigned int wrapS) { this->wrapS = wrapS; }
	void setwrapT(unsigned int wrapT) { this->wrapT = wrapT; }
	void setmagFilter(unsigned int magFilter) { this->magFilter = magFilter; }
	void setminFilter(unsigned int minFilter) { this->minFilter = minFilter; }

	void setTextureData(unsigned int count, unsigned char* data);
	void SelectToChange();
	void Deselect();
	void SelectToRender(int textureUnit);
	void Allocate();

	void LoadTextureDataFromFile(const std::string& filepath);

private: 
	void Cleanup();
};

