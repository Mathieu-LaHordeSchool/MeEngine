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
		// Position (x, y, z)
		-1.f,  1.f, 0.0f,  // Coin sup�rieur gauche
		-1.f, -1.f, 0.0f,  // Coin inf�rieur gauche
		 1.f, -1.f, 0.0f,  // Coin inf�rieur droit
		 1.f,  1.f, 0.0f   // Coin sup�rieur droit
	};
	std::vector<uint32_t>  Elements = {
		0, 1, 2,  // Premier triangle
		0, 2, 3   // Deuxi�me triangle
	};
	std::vector<float> Normals = {
	
	};
	std::vector<float> Uvs = {
		// Coordonn�es UV (u, v)
		0.0f, 0.0f,  // Coin inf�rieur gauche
		0.0f, 1.0f,  // Coin sup�rieur gauche
		1.0f, 1.0f,  // Coin sup�rieur droit
		1.0f, 0.0f   // Coin inf�rieur droit
	};

	void GetBoundsMesh(glm::vec3& min, glm::vec3& max);
	void GetCornersOfBounds(glm::vec3* corners);
};