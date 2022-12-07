#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <map>
#include <glad/glad.h>

class Shader
{
public:
    unsigned int programID;

    explicit Shader(const std::string &filename);
    ~Shader();
    void useProgram() const;
private:
    static const std::map<GLenum, std::string> shaderTypeStrings;

    static unsigned int compileShader(GLenum, const std::string&);
};

#endif
