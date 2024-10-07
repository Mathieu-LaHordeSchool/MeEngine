#version 460 core

layout(location = 0) in vec3 aVerticePosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in mat4 aModel;

uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;

out vec3 normal;

void main() 
{
	normal = aNormal;
	mat4 mvp = uProjectionMatrix * uViewMatrix * aModel;
	gl_Position = mvp * vec4(aVerticePosition, 1.f);
}