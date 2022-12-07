#include "shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

const std::map<GLenum, std::string> Shader::shaderTypeStrings
{
    {GL_VERTEX_SHADER, "VERTEX"},
    {GL_FRAGMENT_SHADER, "FRAGMENT"}
};

static unsigned int createShaderProgram(const std::vector<unsigned int> &shaders)
{
    unsigned int shaderProgram = glCreateProgram();
    for (unsigned int shader : shaders)
    {
        glAttachShader(shaderProgram, shader);
    }
    glLinkProgram(shaderProgram);
    for (unsigned int shader : shaders)
    {
        glDeleteShader(shader);
    }
    return shaderProgram;
}

Shader::Shader(const std::string &filename)
{
    std::string path = "render3d/shaders/" + filename + ".glsl";
    std::string fileContent;
    std::ifstream fileStream;
    std::vector<unsigned int> shaders;
    fileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        std::stringstream fileStreamBuffer;
        fileStream.open(path);
        fileStreamBuffer << fileStream.rdbuf();
        fileStream.close();
        fileContent = fileStreamBuffer.str();
    }
    catch (std::ifstream::failure &log)
    {
        std::cout << "Shader file could not be read.\n" << log.what() << std::endl;
    }
    for (const auto &pair : shaderTypeStrings)
    {
        // .glsl file contains both vertex and fragment shaders, so we prepend the appropriate define to specify which one to compile
        shaders.push_back(compileShader(pair.first, "#version 330 core\n#define " + pair.second + "\n" + fileContent));
    }
    programID = createShaderProgram(shaders);
}

Shader::~Shader()
{
    glDeleteProgram(programID);
}

void Shader::useProgram() const
{
    glUseProgram(programID);
}

void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}

void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(programID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1i(glGetUniformLocation(programID, name.c_str()), static_cast<int>(value));
}

unsigned int Shader::compileShader(GLenum shaderType, const std::string &fileContent)
{
    const char *shaderSource = fileContent.c_str();
    unsigned int shader = glCreateShader(shaderType);
    int success;
    int logLength;
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
    if (!success)
    {
        char log[logLength];
        glGetShaderInfoLog(shader, logLength, nullptr, log);
        std::cout << "Shader " << shaderTypeStrings.at(shaderType) << " compilation failed.\n" << log << std::endl;
    }
    return shader;
}
