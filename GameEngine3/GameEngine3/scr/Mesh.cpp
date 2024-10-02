#include <Mesh/Mesh.h>

#include <unordered_map>

#define TINYOBJLOADER_IMPLEMENTATION
#include <Mesh/tiny_obj_loader.h>

// Update the VertexData structure to include color.
struct VertexData {
    int vertexIndex;
    int texCoordIndex;
    int normalIndex;
    // Assume colors are defined as RGB floating point values.
    float r, g, b, a;

    bool operator==(const VertexData& other) const {
        return vertexIndex == other.vertexIndex &&
            texCoordIndex == other.texCoordIndex &&
            normalIndex == other.normalIndex &&
            r == other.r && g == other.g && b == other.b && a == other.a;
    }
};

namespace std {
    // Update the hash function to include color.
    template<> struct hash<VertexData> {
        size_t operator()(const VertexData& vertexData) const {
            return ((hash<int>()(vertexData.vertexIndex) ^
                (hash<int>()(vertexData.texCoordIndex) << 1) >> 1) ^
                (hash<int>()(vertexData.normalIndex) << 1)) ^
                (hash<float>()(vertexData.r) ^
                    (hash<float>()(vertexData.g) << 1) >> 1) ^
                (hash<float>()(vertexData.b) << 1);
        }
    };
}

void Mesh::LoadObjModel(const char* modelPath)
{
	std::string warn, err;
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, modelPath);

	if (!err.empty()) {
		std::cerr << err << std::endl;
	}
	if (!ret) {
		exit(1);
	}

    std::unordered_map<VertexData, unsigned int> uniqueVertices{};
    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<float> texcoords;
    std::vector<float> colors; // Vector to store color data
    std::vector<unsigned int> indices;

    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            VertexData vertexData{
                index.vertex_index,
                index.texcoord_index,
                index.normal_index,
                // Example color data, replace with actual color retrieval logic
                Color.r, // r
                Color.g, // g
                Color.b, // b
                Color.a // a
            };

            if (uniqueVertices.count(vertexData) == 0) {
                uniqueVertices[vertexData] = static_cast<unsigned int>(vertices.size()) / 3;

                vertices.push_back(attrib.vertices[3 * index.vertex_index]);
                vertices.push_back(attrib.vertices[3 * index.vertex_index + 1]);
                vertices.push_back(attrib.vertices[3 * index.vertex_index + 2]);

                if (!attrib.texcoords.empty()) {
                    texcoords.push_back(attrib.texcoords[2 * index.texcoord_index]);
                    texcoords.push_back(1.0f - attrib.texcoords[2 * index.texcoord_index + 1]);
                }

                if (!attrib.normals.empty()) {
                    normals.push_back(attrib.normals[3 * index.normal_index]);
                    normals.push_back(attrib.normals[3 * index.normal_index + 1]);
                    normals.push_back(attrib.normals[3 * index.normal_index + 2]);
                }

                // Store the color data
                colors.push_back(vertexData.r);
                colors.push_back(vertexData.g);
                colors.push_back(vertexData.b);
                colors.push_back(vertexData.a);
            }

            indices.push_back(uniqueVertices[vertexData]);
        }
    }

    Vertices.swap(vertices);
    Normals.swap(normals);
    TexsUv.swap(texcoords);
    Colors.swap(colors); // Update the Mesh object's color vector
    Elements.swap(indices);
}
