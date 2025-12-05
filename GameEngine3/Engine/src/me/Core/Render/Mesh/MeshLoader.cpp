
#include <me/Core/Render/Mesh/MeshLoader.h>
#include <me/Core/Render/Mesh/Mesh.h>

#include <unordered_map>
#include <iostream>

using namespace me::core::render;

#pragma region OBJ
#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>


// Update the VertexData structure to include color.
struct VertexData {
    int vertexIndex;
    int texCoordIndex;
    int normalIndex;

    bool operator==(const VertexData& other) const {
        return vertexIndex == other.vertexIndex &&
            texCoordIndex == other.texCoordIndex &&
            normalIndex == other.normalIndex;
    }
};

namespace std {
    // Update the hash function to include color.
    template<> struct hash<VertexData> {
        size_t operator()(const VertexData& vertexData) const {
            return ((hash<int>()(vertexData.vertexIndex) ^
                (hash<int>()(vertexData.texCoordIndex) << 1) >> 1) ^
                (hash<int>()(vertexData.normalIndex) << 1));
        }
    };
}

Mesh MeshLoader::LoadObjMesh(const char* modelPath)
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
    std::vector<unsigned int> indices;

    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            VertexData vertexData{
                index.vertex_index,
                index.texcoord_index,
                index.normal_index,
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
            }

            indices.push_back(uniqueVertices[vertexData]);
        }
    }

    Mesh newMesh = Mesh();
    newMesh.path = modelPath;
    newMesh.Vertices.swap(vertices);
    newMesh.Normals.swap(normals);
    newMesh.Uvs.swap(texcoords);
    newMesh.Elements.swap(indices);
    return newMesh;
}
#pragma endregion

#pragma region GLTF

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <tiny_gltf.h>

Mesh MeshLoader::LoadGltfMesh(const char* modelPath)
{
    tinygltf::TinyGLTF loader;
    tinygltf::Model model;
    std::string err;
    std::string warn;

    bool ret = loader.LoadASCIIFromFile(&model, &err, &warn, modelPath);
    if (!warn.empty()) {
        std::cout << "Warning: " << warn << std::endl;
    }
    if (!err.empty()) {
        std::cout << "Error: " << err << std::endl;
    }
    if (!ret) {
        std::cout << "Failed to load GLTF model" << std::endl;
        return Mesh();
    }
    std::cout << "GLTF model loaded successfully" << std::endl;

    std::vector<float> vertices;
    std::vector<float> normals;
    std::vector<float> uvs;
    std::vector<unsigned int> elements;

    for (const auto& mesh : model.meshes) {
        for (const auto& primitive : mesh.primitives) {
            // Vérifier les attributs de la primitive (Position, Normal, UV)
            const auto& posAccessor = model.accessors[primitive.attributes.at("POSITION")];
            const auto& normAccessor = model.accessors[primitive.attributes.at("NORMAL")];
            const auto& uvAccessor = primitive.attributes.count("TEXCOORD_0") > 0
                ? model.accessors[primitive.attributes.at("TEXCOORD_0")]
                : posAccessor; // Utiliser la position si les UVs ne sont pas présents

            const auto& posBufferView = model.bufferViews[posAccessor.bufferView];
            const auto& normBufferView = model.bufferViews[normAccessor.bufferView];
            const auto& uvBufferView = model.bufferViews[uvAccessor.bufferView];

            const auto& posBuffer = model.buffers[posBufferView.buffer];
            const auto& normBuffer = model.buffers[normBufferView.buffer];
            const auto& uvBuffer = model.buffers[uvBufferView.buffer];

            // Extraire les positions, normales et UVs
            for (size_t i = 0; i < posAccessor.count; ++i) {
                // Extraire les positions
                float px = posBuffer.data[posBufferView.byteOffset + posAccessor.byteOffset + i * 3 + 0];
                float py = posBuffer.data[posBufferView.byteOffset + posAccessor.byteOffset + i * 3 + 1];
                float pz = posBuffer.data[posBufferView.byteOffset + posAccessor.byteOffset + i * 3 + 2];

                // Extraire les normales
                float nx = normBuffer.data[normBufferView.byteOffset + normAccessor.byteOffset + i * 3 + 0];
                float ny = normBuffer.data[normBufferView.byteOffset + normAccessor.byteOffset + i * 3 + 1];
                float nz = normBuffer.data[normBufferView.byteOffset + normAccessor.byteOffset + i * 3 + 2];

                // Extraire les UVs
                float u = uvBuffer.data[uvBufferView.byteOffset + uvAccessor.byteOffset + i * 2 + 0];
                float v = uvBuffer.data[uvBufferView.byteOffset + uvAccessor.byteOffset + i * 2 + 1];

                // Ajouter un vertex, normal et UV
                vertices.push_back(px);
                vertices.push_back(py);
                vertices.push_back(pz);

                normals.push_back(nx);
                normals.push_back(ny);
                normals.push_back(nz);

                uvs.push_back(u);
                uvs.push_back(v);

                // Débogage pour vérifier les valeurs
                std::cout << "Vertex " << i << ": (" << px << ", " << py << ", " << pz << ")\n";
                std::cout << "Normal " << i << ": (" << nx << ", " << ny << ", " << nz << ")\n";
                std::cout << "UV " << i << ": (" << u << ", " << v << ")\n";
            }

            // Gestion des indices
            if (primitive.indices >= 0) {
                const auto& indexAccessor = model.accessors[primitive.indices];
                const auto& indexBufferView = model.bufferViews[indexAccessor.bufferView];
                const auto& indexBuffer = model.buffers[indexBufferView.buffer];

                // Vérification des indices et ajout
                for (size_t i = 0; i < indexAccessor.count; ++i) {
                    unsigned int index = 0;
                    if (indexAccessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_SHORT) {
                        index = *((unsigned short*)&indexBuffer.data[indexBufferView.byteOffset + indexAccessor.byteOffset + i * 2]);
                    }
                    else if (indexAccessor.componentType == TINYGLTF_COMPONENT_TYPE_UNSIGNED_INT) {
                        index = *((unsigned int*)&indexBuffer.data[indexBufferView.byteOffset + indexAccessor.byteOffset + i * 4]);
                    }

                    // Vérifier que l'indice est dans la plage des vertices
                    if (index < vertices.size() / 3) {
                        elements.push_back(index);
                    }
                    else {
                        std::cout << "Indice invalide : " << index << ", il doit être inférieur à " << vertices.size() / 3 << "\n";
                    }
                }
            }

        }
    }

    Mesh mesh;
    mesh.path = modelPath;

    mesh.Vertices.swap(vertices);
    mesh.Normals.swap(normals);
    mesh.Uvs.swap(uvs);
    mesh.Elements.swap(elements);

    return mesh;
}

#pragma endregion
