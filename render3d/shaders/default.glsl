#ifdef VERTEX

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texel;
out vec2 vertexTexel;
uniform mat4 combination;

void main()
{
    gl_Position = combination * vec4(pos, 1.0f);
    vertexTexel = texel;
}

#endif
#ifdef FRAGMENT

out vec4 fragmentColor;
in vec2 vertexTexel;
uniform sampler2D textureData;

void main()
{
    fragmentColor = texture(textureData, vertexTexel);
}

#endif
