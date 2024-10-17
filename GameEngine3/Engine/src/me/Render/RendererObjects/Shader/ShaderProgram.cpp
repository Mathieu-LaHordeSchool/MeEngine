
#include <me/Render/RendererObjects/Shader/ShaderProgram.h>
#include <me/Render/RendererObjects/Shader/Shader.h>

#include <GL/glew.h>
#include <iostream>

using namespace me::render::shader;

struct ShaderProgram::Internal
{
	uint32_t shaderProgram;
};

ShaderProgram::ShaderProgram(Shader* vs, Shader* fs)
	: m_program(new Internal())
{
	m_program->shaderProgram = glCreateProgram();
	glAttachShader(m_program->shaderProgram, vs->GetShader());
	glAttachShader(m_program->shaderProgram, fs->GetShader());
	glLinkProgram(m_program->shaderProgram);

	glDeleteShader(vs->GetShader());
	glDeleteShader(fs->GetShader());

	int linkStatus = 0;
	glGetProgramiv(m_program->shaderProgram, GL_LINK_STATUS, &linkStatus);
	if (linkStatus == GL_FALSE)
	{
		char log[4096];
		glGetShaderInfoLog(m_program->shaderProgram, 4096, nullptr, log);
		std::cout << "program failed to link" << std::endl;
		std::cout << log << std::endl;
		std::cout << "==================================" << std::endl;
	}
}
ShaderProgram::~ShaderProgram() noexcept
{
	glDeleteProgram(m_program->shaderProgram);
}

uint32_t ShaderProgram::GetShaderProgram() const
{
	return m_program->shaderProgram;
}
void ShaderProgram::StartShaderProgram()
{
	glUseProgram(m_program->shaderProgram);
}
void ShaderProgram::StopShaderProgram()
{
	glUseProgram(0);
}

void ShaderProgram::SetMat4(const char* name, const glm::mat4& value)
{
	int location = glGetUniformLocation(GetShaderProgram(), name);
	glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
}
void ShaderProgram::SetVec4(const char* name, const glm::vec4& value)
{
	int location = glGetUniformLocation(GetShaderProgram(), name);
	glUniform4f(location, value.x, value.y, value.z, value.w);
}
void ShaderProgram::SetVec3(const char* name, const glm::vec3& value)
{
	int location = glGetUniformLocation(GetShaderProgram(), name);
	glUniform3f(location, value.x, value.y, value.z);
}
void ShaderProgram::SetVec2(const char* name, const glm::vec2& value)
{
	int location = glGetUniformLocation(GetShaderProgram(), name);
	glUniform2f(location, value.x, value.y);
}
void ShaderProgram::SetSampler2D(const char* name, int sampler)
{
	int location = glGetUniformLocation(GetShaderProgram(), name);
	glUniform1i(location, sampler);
}
