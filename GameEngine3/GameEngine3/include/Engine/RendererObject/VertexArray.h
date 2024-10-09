#pragma once

#include <cstdint>
#include <RendererObject/Buffer.h>
#include <GL/glew.h>

class VertexArrayObject
{
public:
	explicit VertexArrayObject();
	~VertexArrayObject() noexcept;

public:
	template<typename T> void BindingBuffer(int bindingIndex, int offset, Buffer* buffer, int sizeT = 1) {
		glVertexArrayVertexBuffer(vaoId, bindingIndex, buffer->GetBuffer(), offset, sizeof(T) * sizeT);
	}
	void AttributeBinding(int bindIndex, int layoutIndex, int size, unsigned int type, unsigned int normalize, int offset);

	void BindVertexArray();
	void UnbindVertexArray();
	void BindMapBuffer(int bufferIndex, int div);
	void BindAttribDivisor(int attribIndex, int div);

	void BindElementBuffer(Buffer* elementBuffer);

	inline uint32_t GetID() const { return vaoId; }

private:
	uint32_t vaoId;
};
