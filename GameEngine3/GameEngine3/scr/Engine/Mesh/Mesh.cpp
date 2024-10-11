#include <Engine/Mesh/Mesh.h>

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
