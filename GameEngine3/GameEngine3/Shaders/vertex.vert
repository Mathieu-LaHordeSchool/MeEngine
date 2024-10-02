#version 460 core

layout(location = 0) in vec3 aVerticePosition;
layout(location = 1) in vec3 aPosition;

uniform mat4 uViewMatrix;
uniform mat4 uProjectionMatrix;

void main() 
{
	mat4 mvp = uProjectionMatrix * uViewMatrix;
	gl_Position = mvp * vec4(aVerticePosition + aPosition, 1.f);
}