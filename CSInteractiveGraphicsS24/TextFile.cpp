#include "TextFile.h"
#include "string"
#include <sstream>
#include <fstream>

TextFile::TextFile(const std::string& filePath)
{
	if (OpenFile(filePath))
	{
		ReadFile(filePath);
	}
}

bool TextFile::OpenFile(const std::string& filePath)
{
	fin.open(filePath.c_str());
	if (fin.fail())
	{
		ss << "Could not open: " << filePath << std::endl; 
		return false;
	}
	return true;
}

void TextFile::ReadFile(const std::string& filePath)
{
	std::string line;
	while (!fin.eof())
	{
		getline(fin, line);
		Trim(line);
		if (line != "") //skip blank lines
		{
			ss << line << std::endl;
		}
	}
	fin.close();
}

void TextFile::Trim(std::string& str)
{
	const std::string delimiters = " \f\n\r\t\v";
	str.erase(str.find_last_not_of(delimiters) + 1);
	str.erase(0, str.find_first_not_of(delimiters));
}
