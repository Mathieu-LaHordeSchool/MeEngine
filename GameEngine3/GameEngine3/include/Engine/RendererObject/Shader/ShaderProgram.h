#pragma once

#include <cstdint>

class Shader;

class ShaderProgram
{
public:
	explicit ShaderProgram(Shader* vs, Shader* fs);
	~ShaderProgram() noexcept;

private:
	uint32_t shaderProgram;

public:
	inline uint32_t GetShaderProgram() const { return shaderProgram;}

	void StartShaderProgram();
	void StopShaderProgram();
};