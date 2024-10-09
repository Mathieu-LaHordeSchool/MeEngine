#include <Engine/RendererObject/Shader/ShaderProgram.h>

#include <GL/glew.h>
#include <iostream>
#include <Engine/RendererObject/Shader/Shader.h>

ShaderProgram::ShaderProgram(Shader* vs, Shader* fs)
{
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vs->GetShader());
	glAttachShader(shaderProgram, fs->GetShader());
	glLinkProgram(shaderProgram);

	glDeleteShader(vs->GetShader());
	glDeleteShader(fs->GetShader());

	int linkStatus = 0;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkStatus);
	if (linkStatus == GL_FALSE)
	{
		char log[4096];
		glGetShaderInfoLog(shaderProgram, 4096, nullptr, log);
		std::cout << "program failed to link" << std::endl;
		std::cout << log << std::endl;
		std::cout << "==================================" << std::endl;
	}
}

ShaderProgram::~ShaderProgram() noexcept
{
	glDeleteProgram(shaderProgram);
}

void ShaderProgram::StartShaderProgram()
{
	glUseProgram(shaderProgram);
}

void ShaderProgram::StopShaderProgram()
{
	glUseProgram(0);
}
