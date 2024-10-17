#pragma once

#include <vector>
#include <glm/glm.hpp>

namespace me::core::render {
	class Mesh
	{
	public:
		explicit Mesh() = default;
		~Mesh() noexcept = default;

		const char* path;
		std::vector<float> Vertices = {
			// Position (x, y, z)
			-1.f,  1.f, 0.0f,  // Coin supérieur gauche
			-1.f, -1.f, 0.0f,  // Coin inférieur gauche
			 1.f, -1.f, 0.0f,  // Coin inférieur droit
			 1.f,  1.f, 0.0f   // Coin supérieur droit
		};
		std::vector<uint32_t>  Elements = {
			0, 1, 2,  // Premier triangle
			0, 2, 3   // Deuxième triangle
		};
		std::vector<float> Normals = {

		};
		std::vector<float> Uvs = {
			// Coordonnées UV (u, v)
			0.0f, 0.0f,  // Coin inférieur gauche
			0.0f, 1.0f,  // Coin supérieur gauche
			1.0f, 1.0f,  // Coin supérieur droit
			1.0f, 0.0f   // Coin inférieur droit
		};

		void GetBoundsMesh(glm::vec3& min, glm::vec3& max);
		void GetCornersOfBounds(glm::vec3* corners);
	};
}
