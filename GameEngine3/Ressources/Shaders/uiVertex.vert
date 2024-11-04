#version 460 core

layout(location = 0) in vec3 aVerticePosition;
layout(location = 2) in vec2 aUvs;

uniform mat4 uModel;
uniform mat4 uProjection;

out vec2 uvs;

void main()
{
	uvs = aUvs;

	gl_Position = uProjection * uModel * vec4(aVerticePosition, 1.f);
}