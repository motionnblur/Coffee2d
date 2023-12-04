#include <string>
#include <fstream>

const char* ReadFile(const std::string& fileName)
{
	std::ifstream file(fileName);
	
	file.seekg(0, std::ios::end);
	size_t fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	char* buffer = new char[fileSize+1];
	file.read(buffer, fileSize);
	buffer[fileSize] = '\0';

	return buffer;
}