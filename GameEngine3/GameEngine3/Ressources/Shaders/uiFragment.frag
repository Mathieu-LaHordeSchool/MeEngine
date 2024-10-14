#version 460 core

layout(location = 0) out vec4 oFragColor;

uniform sampler2D texture;
in vec2 uvs;

void main()
{
	oFragColor = vec4(texture(texture, uvs));
}
