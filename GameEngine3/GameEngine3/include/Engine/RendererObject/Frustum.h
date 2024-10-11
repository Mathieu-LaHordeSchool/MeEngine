
#include <glm/glm.hpp>

class Frustum {
public:
    Frustum(const glm::mat4& viewProjectionMatrix) {
        // Extract frustum planes from view-projection matrix
        planes[0] = viewProjectionMatrix[3] + viewProjectionMatrix[0]; // Left
        planes[1] = viewProjectionMatrix[3] - viewProjectionMatrix[0]; // Right
        planes[2] = viewProjectionMatrix[3] + viewProjectionMatrix[1]; // Bottom
        planes[3] = viewProjectionMatrix[3] - viewProjectionMatrix[1]; // Top
        planes[4] = viewProjectionMatrix[3] + viewProjectionMatrix[2]; // Near
        planes[5] = viewProjectionMatrix[3] - viewProjectionMatrix[2]; // Far

        // Normalize planes
        for (int i = 0; i < 6; ++i) {
            planes[i] = glm::normalize(planes[i]);
        }
    }

    bool IsSphereInsideFrustum(const glm::vec3& center, float radius) const {
        for (int i = 0; i < 6; ++i) {
            float distance = glm::dot(glm::vec4(center, 1.0f), planes[i]);
            if (distance < -radius) {
                // Sphere is completely outside this plane
                return false;
            }
        }
        return true;
    }

    bool IsPointInsideFrustum(const glm::vec3& point) const {
        for (int i = 0; i < 6; ++i) {
            float distance = glm::dot(glm::vec4(point, 1.0f), planes[i]);
            if (distance < 0) {
                // Point is behind this plane
                return false;
            }
        }
        return true;
    }

    bool IsLineInsideFrustum(const glm::vec3& start, const glm::vec3& end) const {
        // Check if both start and end points are inside the frustum
        if (!IsPointInsideFrustum(start) || !IsPointInsideFrustum(end))
            return false;

        // Check if the line intersects any frustum plane
        for (int i = 0; i < 6; ++i) {
            if (glm::dot(glm::vec4(start, 1.0f), planes[i]) * glm::dot(glm::vec4(end, 1.0f), planes[i]) < 0)
                return true; // Intersection found
        }
        return false;
    }

    bool IsCubeVisible(const glm::vec3& corner1, const glm::vec3& corner2) const {
        // Calculate dimensions of the cube
        glm::vec3 cubeCenter = (corner1 + corner2) * 0.5f;
        glm::vec3 cubeSize = glm::abs(corner2 - corner1);

        // Check if any vertex of the cube is inside the frustum
        glm::vec3 halfSize = cubeSize * 0.5f;
        glm::vec3 vertices[8] = {
            cubeCenter + glm::vec3(-halfSize.x, -halfSize.y, -halfSize.z),
            cubeCenter + glm::vec3(halfSize.x, -halfSize.y, -halfSize.z),
            cubeCenter + glm::vec3(-halfSize.x, halfSize.y, -halfSize.z),
            cubeCenter + glm::vec3(halfSize.x, halfSize.y, -halfSize.z),
            cubeCenter + glm::vec3(-halfSize.x, -halfSize.y, halfSize.z),
            cubeCenter + glm::vec3(halfSize.x, -halfSize.y, halfSize.z),
            cubeCenter + glm::vec3(-halfSize.x, halfSize.y, halfSize.z),
            cubeCenter + glm::vec3(halfSize.x, halfSize.y, halfSize.z)
        };

        int numInside = 0;

        for (int i = 0; i < 8; ++i) {
            if (IsPointInsideFrustum(vertices[i]))
                numInside++;
        }

        if (numInside == 8)
            return true; // All vertices are inside

        //if (numInside == 0)
        //    return false; // All vertices are outside

        // Check if any edge of the cube is inside the frustum
        glm::vec3 edges[12][2] = {
            {vertices[0], vertices[1]}, {vertices[0], vertices[2]}, {vertices[0], vertices[4]},
            {vertices[1], vertices[3]}, {vertices[1], vertices[5]}, {vertices[2], vertices[3]},
            {vertices[2], vertices[6]}, {vertices[3], vertices[7]}, {vertices[4], vertices[5]},
            {vertices[4], vertices[6]}, {vertices[5], vertices[7]}, {vertices[6], vertices[7]}
        };

        for (int i = 0; i < 12; ++i) {
            if (IsLineInsideFrustum(edges[i][0], edges[i][1]))
                return true;
        }

        return false;
    }

private:
    glm::vec4 planes[6]; // Plane equations representing the frustum
};

