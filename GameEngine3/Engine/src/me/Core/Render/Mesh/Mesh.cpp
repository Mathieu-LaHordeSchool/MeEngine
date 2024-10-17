
#include <me/Core/Render/Mesh/Mesh.h>

void Mesh::GetBoundsMesh(glm::vec3& min, glm::vec3& max)
{
    if (Vertices.empty()) return;

    min = max = glm::vec3(
        Vertices[0],
        Vertices[1],
        Vertices[2]
    );

    for (size_t i = 1; i < Vertices.size() / 3; ++i)
    {
        glm::vec3 pos = glm::vec3(
            Vertices[i * 3 + 0],
            Vertices[i * 3 + 1],
            Vertices[i * 3 + 2]
        );

        min.x = std::min(min.x, pos.x);
        min.y = std::min(min.y, pos.y);
        min.z = std::min(min.z, pos.z);

        max.x = std::max(max.x, pos.x);
        max.y = std::max(max.y, pos.y);
        max.z = std::max(max.z, pos.z);
    }
}
void Mesh::GetCornersOfBounds(glm::vec3* corners)
{
    // R�cup�re les points minimum et maximum du bounding box
    glm::vec3 min, max;
    GetBoundsMesh(min, max);

    // Les 8 coins de la bo�te englobante
    corners[0] = glm::vec3(min.x, min.y, min.z); // Coin inf�rieur-gauche-arri�re
    corners[1] = glm::vec3(max.x, min.y, min.z); // Coin inf�rieur-droit-arri�re
    corners[2] = glm::vec3(min.x, max.y, min.z); // Coin sup�rieur-gauche-arri�re
    corners[3] = glm::vec3(max.x, max.y, min.z); // Coin sup�rieur-droit-arri�re

    corners[4] = glm::vec3(min.x, min.y, max.z); // Coin inf�rieur-gauche-avant
    corners[5] = glm::vec3(max.x, min.y, max.z); // Coin inf�rieur-droit-avant
    corners[6] = glm::vec3(min.x, max.y, max.z); // Coin sup�rieur-gauche-avant
    corners[7] = glm::vec3(max.x, max.y, max.z); // Coin sup�rieur-droit-avant
}
