#pragma once

#include <vector>
#include <map>

class Buffer;

class RenderObjectData
{

public:
	Buffer* GetOrCreateVertexBuffer(std::vector<float> data);
	Buffer* GetOrCreateUvsBuffer(std::vector<float> data);
	Buffer* GetOrCreateElementBuffer(std::vector<uint32_t> data);
	Buffer* GetOrCreateNormalBuffer(std::vector<float> data);

private:
	std::map<std::vector<float>, Buffer*>		vertexBuffers;
	std::map<std::vector<float>, Buffer*>		textureCoordBuffers;
	std::map<std::vector<float>, Buffer*>		normalBuffer;
	std::map<std::vector<uint32_t>, Buffer*>	elementBuffers;
};
