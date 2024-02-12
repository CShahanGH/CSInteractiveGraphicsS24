#pragma once
#include <sstream>
#include <fstream>
#include <string>


class TextFile
{
private:
	std::stringstream ss;
	std::ifstream fin{};  

public: 
	TextFile(const std::string& filePath);
	~TextFile() = default;

	inline std::string GetData() const { return ss.str(); }

private: 
	bool OpenFile(const std::string& filePath);
	void ReadFile(const std::string& filePath);
	void Trim(std::string& str);

};

