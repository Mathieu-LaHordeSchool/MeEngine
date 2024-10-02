#pragma once

#include <string>

enum EShaderType
{
	Vertex,
	Fragment
};

class Shader
{
public:
	explicit Shader(const char* path, EShaderType shaderType);
	~Shader() noexcept;

	inline uint32_t GetShader() const { return shader; };

private:
	char* GetShaderFromPath(const char* path);

	void compileVertexShader(const char* shaderPath);
	void ComplieFragmentShader(const char* shaderPath);

private:
	uint32_t shader;
};
