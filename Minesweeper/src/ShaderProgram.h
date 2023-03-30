#ifndef SHADER_PROGRAM_CLASS
#define SHADER_PROGRAM_CLASS
#include <glad/glad.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ShaderProgram
{
public:
	unsigned int m_Id;
public:
	ShaderProgram(const char* vertexShaderFilePath, const char* fragmentShaderFilePath);
	~ShaderProgram();
	void Activate() const;
	void SetVector4f(const char* name, const glm::vec4& value) const;
private:
	void CompileErrors(unsigned int shader, const char* type) const;
	std::string GetFileContents(const char* path) const;
	void Delete() const;

};
#endif