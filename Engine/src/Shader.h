#ifndef SHADER_H
#define SHADER_H

#include <sstream>
#include <fstream>
#include <iostream>
#include <glad/glad.h>

enum class ShaderType
{
	VERTEX,
	FRAGMENT
};

class Shader
{
	ShaderType m_Type;

	std::string m_SourceString;
	const char* m_SourceCode;

	unsigned int m_ShaderID;

	std::string parseShader(const std::string& filePath);

public:
	Shader(const std::string& filePath, ShaderType shaderType);
	~Shader();

};

#endif // !SHADER_H
