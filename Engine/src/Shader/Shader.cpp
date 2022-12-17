#include "Shader.h"

Shader::Shader(const std::string& filePath, ShaderType shaderType)
{
    m_Type = shaderType;
    m_SourceString = parseShader(filePath);
    m_SourceCode = m_SourceString.c_str();

    switch (m_Type)
    {
    case ShaderType::VERTEX:
        m_ShaderID = glCreateShader(GL_VERTEX_SHADER);
        break;
    case ShaderType::FRAGMENT:
        m_ShaderID = glCreateShader(GL_FRAGMENT_SHADER);
        break;
    default:
        break;
    }

    glShaderSource(m_ShaderID, 1, &m_SourceCode, nullptr);
    glCompileShader(m_ShaderID);

    // check for shader compile errors
    int success;
    glGetShaderiv(m_ShaderID, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE)
    {
        int length;
        glGetShaderiv(m_ShaderID, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(m_ShaderID, length, &length, message);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << message << std::endl;
    }
}

Shader::~Shader()
{

}

std::string Shader::parseShader(const std::string& filePath)
{
    std::ifstream stream(filePath);

    std::stringstream ss;
    std::string line;
    while (std::getline(stream, line))
    {
        ss << line << '\n';
    }

    return ss.str();
}

unsigned int Shader::getID()
{
    return m_ShaderID;
}

void Shader::bind()
{
    glUseProgram(m_ShaderID);
}

void Shader::unbind()
{
    glUseProgram(0);
}

void Shader::uploadUniformInt(const std::string& name, int value)
{

}

void Shader::uploadUniformFloat(const std::string& name, float value)
{

}

void Shader::uploadUniformFloat2(const std::string& name, const glm::vec2& value)
{

}

void Shader::uploadUniformFloat3(const std::string& name, const glm::vec3& value)
{

}

void Shader::uploadUniformFloat4(const std::string& name, const glm::vec4& value)
{

}

void Shader::uploadUniformMat3(const std::string& name, const glm::mat3& matrix)
{

}

void Shader::uploadUniformMat4(const std::string& name, const glm::mat4& matrix)
{

}