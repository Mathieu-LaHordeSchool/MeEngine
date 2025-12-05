#pragma once

namespace me::core::render {
	class MeshLoader
	{
	public:
		class Mesh LoadObjMesh(const char* modelPath);
		class Mesh LoadGltfMesh(const char* modelPath);
	};
}
