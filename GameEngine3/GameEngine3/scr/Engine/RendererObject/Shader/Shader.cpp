#include <Engine/RendererObject/Shader/Shader.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <stdio.h>

#include <GL/glew.h>

Shader::Shader(const char* path, EShaderType shaderType)
{
	switch (shaderType)
	{
	case Vertex:   compileVertexShader(path);   break;
	case Fragment: ComplieFragmentShader(path);	break;
	default: break;
	}
}

Shader::~Shader()
{
	glDeleteShader(shader);
}

char* Shader::GetShaderFromPath(const char* path)
{
	std::ifstream file(path);

	if (!file.is_open())
	{
		std::cerr << "Failed to open file: " << path << std::endl;
		return nullptr;
	}

	std::stringstream buffer;
	buffer << file.rdbuf();

	std::string str = buffer.str(); // Use a std::string to hold the contents temporarily
	char* result = new char[str.size() + 1]; // Allocate memory for the char array

	// Use strcpy_s instead of strcpy
	strcpy_s(result, str.size() + 1, str.c_str()); // Copy the string into the allocated array, safely

	return result; // Return the dynamically allocated array
}

void Shader::compileVertexShader(const char* shaderPath)
{
	const char* shaderSource = GetShaderFromPath(shaderPath);

	shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(shader, 1, &shaderSource, nullptr);
	glCompileShader(shader);

	int ComplileStatus = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &ComplileStatus);
	if (ComplileStatus == GL_FALSE)
	{
		char log[4096];
		glGetShaderInfoLog(shader, 4096, nullptr, log);
		std::cout << "Vertex shader failed to complile" << std::endl;
		std::cout << log << std::endl;
		std::cout << "================================" << std::endl;
	}
}

void Shader::ComplieFragmentShader(const char* shaderPath)
{
	const char* shaderSource = GetShaderFromPath(shaderPath);

	shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(shader, 1, &shaderSource, nullptr);
	glCompileShader(shader);

	int ComplileStatus = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &ComplileStatus);
	if (ComplileStatus == GL_FALSE)
	{
		char log[4096];
		glGetShaderInfoLog(shader, 4096, nullptr, log);
		std::cout << "fragment shader failed to complile" << std::endl;
		std::cout << log << std::endl;
		std::cout << "==================================" << std::endl;
	}
}
