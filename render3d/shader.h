#ifndef SHADER_H
#define SHADER_H

class Shader
{
public:
    unsigned int id;

    Shader(const char *vertexSourcePath, const char *fragmentSourcePath);
};

#endif
