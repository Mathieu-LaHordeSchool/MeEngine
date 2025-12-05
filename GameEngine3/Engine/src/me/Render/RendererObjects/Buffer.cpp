
#include <me/Render/RendererObjects/Buffer.h>

#include <cstdint>
#include <GL/glew.h>

using namespace me::render::object;

// other update b

Buffer::Buffer()
{
	glCreateBuffers(1, &buffer);
}

Buffer::~Buffer() noexcept
{
	if (mappedBuffer)
		glUnmapNamedBuffer(buffer);

	glDeleteBuffers(1, &buffer);

}

void Buffer::InitBuffer(int size, void* value)
{
	glNamedBufferStorage(buffer, size, value, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
	mappedBuffer = glMapNamedBufferRange(buffer, 0, size, GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT);
}

void Buffer::SubData(int offset, int size, void* data)
{
	glNamedBufferSubData(buffer, offset, size, data);
}
