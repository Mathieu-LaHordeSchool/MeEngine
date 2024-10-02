#pragma once

#include <glm/glm.hpp>
#include <Texture/texture.h>
#include <vector>
#include <iostream>

class Mesh
{
public:
	explicit Mesh(const char* modelPath, Texture* texture, glm::vec4 color = glm::vec4(1.f)) {
		this->texture = texture;
		Color = color;
		LoadObjModel(modelPath);
	}
	explicit Mesh(const char* modelPath) 
		: Color(glm::vec4(1.f))
	{
		LoadObjModel(modelPath);
	}
	explicit Mesh()
		: Color(glm::vec4(1.f))
	{}

	~Mesh() noexcept = default;

public:
	std::vector<float> Vertices = {
		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
						
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f
	};
	std::vector<uint32_t>  Elements = {
		0, 1, 2,
		2, 3, 0,

		1, 5, 6,
		6, 2, 1,

		7, 6, 5,
		5, 4, 7,

		4, 0, 3,
		3, 7, 4,

		4, 5, 1,
		1, 0, 4,

		3, 2, 6,
		6, 7, 3
	};
	std::vector<float> Colors = {
		1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f,

		1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f,
		1.f, 1.f, 1.f, 1.f
	};
	std::vector<float> Normals = {
		 1.f, 1.f,  1.f,
		 1.f, 1.f,  1.f,
		 1.f, 1.f,  1.f,
		 1.f, 1.f,  1.f,

		 1.f, 1.f,  1.f,
		 1.f, 1.f,  1.f,
		 1.f, 1.f,  1.f,
		 1.f, 1.f,  1.f
	};
	std::vector<float> TexsUv = {
		1.f, 1.f,
		1.f, 0.f,
		0.f, 0.f,
		0.f, 1.f,

		1.f, 1.f,
		1.f, 0.f,
		0.f, 0.f,
		0.f, 1.f
	};

	Texture* texture;
	glm::vec4 Color;

private:
	void LoadObjModel(const char* modelPath);
};