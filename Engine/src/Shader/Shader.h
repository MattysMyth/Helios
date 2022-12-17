#ifndef SHADER_H
#define SHADER_H

#include <sstream>
#include <fstream>
#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>

enum class ShaderType
{
	VERTEX,
	FRAGMENT
};

// Shader object that translates and stores shader code from external files into GPU friendly strings. Essentially
// a CPU image of a Shader before being linked to a Program on the GPU
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

	unsigned int getID();

	void bind();

	void unbind();

	void uploadUniformInt(const std::string& name, int value);

	void uploadUniformFloat(const std::string& name, float value);
	void uploadUniformFloat2(const std::string& name, const glm::vec2& value);
	void uploadUniformFloat3(const std::string& name, const glm::vec3& value);
	void uploadUniformFloat4(const std::string& name, const glm::vec4& value);

	void uploadUniformMat3(const std::string& name, const glm::mat3& matrix);
	void uploadUniformMat4(const std::string& name, const glm::mat4& matrix);
};

#endif // !SHADER_H
