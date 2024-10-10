
#include <iostream>

#include <Engine/RendererObject/RenderObjectData.h>
#include <Engine/RendererObject/Buffer.h>

Buffer* RenderObjectData::GetOrCreateVertexBuffer(std::vector<float> data)
{
	if (vertexBuffers.count(data) == 0) {
		std::cout << "create vertex buffer" << std::endl;

		Buffer* newBuffer = new Buffer();
		newBuffer->InitBuffer<float>(data);
		vertexBuffers[data] = newBuffer;
		return newBuffer;
	}

	return vertexBuffers[data];
}
Buffer* RenderObjectData::GetOrCreateUvsBuffer(std::vector<float> data)
{
	if (textureCoordBuffers.count(data) == 0) {
		std::cout << "create texture buffer" << std::endl;

		Buffer* newBuffer = new Buffer();
		newBuffer->InitBuffer<float>(data);
		textureCoordBuffers[data] = newBuffer;
		return newBuffer;
	}

	return textureCoordBuffers[data];
}
Buffer* RenderObjectData::GetOrCreateElementBuffer(std::vector<uint32_t> data)
{
	if (elementBuffers.count(data) == 0) {
		std::cout << "create element buffer" << std::endl;

		Buffer* newBuffer = new Buffer();
		newBuffer->InitBuffer<uint32_t>(data);
		elementBuffers[data] = newBuffer;
		return newBuffer;
	}

	return elementBuffers[data];
}

Buffer* RenderObjectData::GetOrCreateNormalBuffer(std::vector<float> data)
{
	if (normalBuffer.count(data) == 0) {
		std::cout << "create normal buffer" << std::endl;

		Buffer* newBuffer = new Buffer();
		newBuffer->InitBuffer<float>(data);
		normalBuffer[data] = newBuffer;
		return newBuffer;
	}

	return normalBuffer[data];
}
