#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <map>
#include <glad/glad.h>

class Shader
{
public:
    unsigned int programID;

    explicit Shader(const std::string&);
    ~Shader();
    void useProgram() const;
    void setBool(const std::string&, bool) const;
    void setInt(const std::string&, int) const;
    void setFloat(const std::string&, float) const;
private:
    static const std::map<GLenum, std::string> shaderTypeStrings;

    static unsigned int compileShader(GLenum, const std::string&);
};

#endif
