#ifndef SHADER_PROGRAM_CLASS
#define SHADER_PROGRAM_CLASS
#include <glad/glad.h>
#include <fstream>
#include <iostream>
#include <sstream>


class ShaderProgram
{
public:
	unsigned int m_Id;
public:
	ShaderProgram(const char* vertexShaderFilePath, const char* fragmentShaderFilePath);
	~ShaderProgram();
	void Activate() const;
private:
	void CompileErrors(unsigned int shader, const char* type) const;
	std::string GetFileContents(const char* path) const;
	void Delete() const;

};
#endif