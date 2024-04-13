#pragma once
#include <glad/glad.h> 
#include <vector>
class IndexBuffer
{
private:
	unsigned int iboId;
	std::vector<unsigned short> indexData;

public:
	IndexBuffer();
	~IndexBuffer();

	inline void Select() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId); }
	inline void Deselect() { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

	std::vector<unsigned short>& GetIndexeData() { return indexData; } //Lab 8 3.3.1
	int GetNumberOfIndexes() { return indexData.size(); }
	void AddIndexData(unsigned int count, ...);
	void AddIndexData(unsigned short index);
	void StaticAllocate();

};

