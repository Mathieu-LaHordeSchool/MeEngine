#pragma once

namespace me::core::render {
	class MeshLoader
	{
	public:
		class Mesh LoadMesh(const char* modelPath);
	};
}
