#ifdef VERTEX

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;
out vec3 vertexColor;
uniform bool test;

void main()
{
    gl_Position = vec4(pos, 1.0f);
    vertexColor = color;
}

#endif
#ifdef FRAGMENT

out vec4 fragmentColor;
in vec3 vertexColor;

void main()
{
    fragmentColor = vec4(vertexColor, 1.0f);
}

#endif
