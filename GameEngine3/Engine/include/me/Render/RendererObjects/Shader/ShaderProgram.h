#pragma once

#include <cstdint>
#include <glm/glm.hpp>

namespace me::render::shader {
	class Shader;

	class ShaderProgram
	{
		struct Internal;
		Internal* m_program;

	public:
		explicit ShaderProgram(Shader* vs, Shader* fs);
		~ShaderProgram() noexcept;

	public:
		uint32_t GetShaderProgram() const;

		void StartShaderProgram();
		void StopShaderProgram();

		void SetMat4(const char* name, const glm::mat4& value);
		void SetVec4(const char* name, const glm::vec4& value);
		void SetVec3(const char* name, const glm::vec3& value);
		void SetVec2(const char* name, const glm::vec2& value);
		void SetSampler2D(const char* name, int sampler);
	};
}

