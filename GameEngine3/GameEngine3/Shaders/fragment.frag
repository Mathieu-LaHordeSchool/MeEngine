#version 460 core

layout(location = 0) out vec4 oFragColor;

in vec3 normal;

void main() 
{
	oFragColor = vec4(normal, 1.f);
}
