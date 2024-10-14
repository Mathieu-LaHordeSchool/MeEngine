#version 460 core

layout(location = 0) in vec3 aVerticePosition;
layout(location = 2) in vec2 aUvs;

uniform mat4 uModel;

out vec3 position;
out vec2 uvs;

void main()
{
	position = aVerticePosition;
	uvs = aUvs;

	gl_Position = uModel * vec4(aVerticePosition, 1.f);
}