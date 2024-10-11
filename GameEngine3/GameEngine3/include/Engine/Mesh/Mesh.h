#pragma once

#include <vector>
#include <glm/glm.hpp>

class Mesh
{
public:
	explicit Mesh() = default;
	~Mesh() noexcept = default;
	
	const char* path;
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
	std::vector<float> Uvs = {
		1.f, 1.f,
		1.f, 0.f,
		0.f, 0.f,
		0.f, 1.f,

		1.f, 1.f,
		1.f, 0.f,
		0.f, 0.f,
		0.f, 1.f
	};

	void GetBoundsMesh(glm::vec3& min, glm::vec3& max);
	void GetCornersOfBounds(glm::vec3* corners);
};