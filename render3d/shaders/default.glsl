#ifdef VERTEX

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texel;
out vec3 vertexColor;
out vec2 vertexTexel;

void main()
{
    gl_Position = vec4(pos, 1.0f);
    vertexColor = color;
    vertexTexel = texel;
}

#endif
#ifdef FRAGMENT

out vec4 fragmentColor;
in vec3 vertexColor;
in vec2 vertexTexel;
uniform sampler2D textureData;

void main()
{
    fragmentColor = texture(textureData, vertexTexel);
}

#endif
