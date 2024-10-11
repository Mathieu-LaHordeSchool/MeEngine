#version 460 core

layout(location = 0) in vec3 aVerticePosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aUvs;

uniform mat4 uModel;

uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;

out vec3 position;
out vec3 normal;
out vec2 uvs;

void main() 
{
	position = aVerticePosition;
	normal = aNormal;
	uvs = aUvs;

	mat4 mvp = uProjectionMatrix * uViewMatrix * uModel;
	gl_Position = mvp * vec4(aVerticePosition, 1.f);
}