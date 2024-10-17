
#include <me/Render/RendererObjects/VertexArray.h>
#include <me/Render/RendererObjects/Buffer.h>

#include <GL/glew.h>

using namespace me::render::object;

VertexArrayObject::VertexArrayObject()
{
	glCreateVertexArrays(1, &vaoId);
}

VertexArrayObject::~VertexArrayObject() noexcept
{
	glDeleteVertexArrays(1, &vaoId);
}

void VertexArrayObject::BindingBuffer(int bindingIndex, int offset, me::render::object::Buffer* buffer, int stripe)
{
	glVertexArrayVertexBuffer(vaoId, bindingIndex, buffer->GetBuffer(), offset, stripe);
}

void VertexArrayObject::AttributeBinding(int bindIndex, int layoutIndex, int size, unsigned int type, unsigned int normalize, int offset)
{
	glEnableVertexArrayAttrib(vaoId, layoutIndex);
	glVertexArrayAttribBinding(vaoId, layoutIndex, bindIndex);
	glVertexArrayAttribFormat(vaoId, layoutIndex, size, type, normalize, offset);
}

void VertexArrayObject::BindVertexArray()
{
	glBindVertexArray(vaoId);
}

void VertexArrayObject::UnbindVertexArray()
{
	glBindVertexArray(0);
}

void VertexArrayObject::BindMapBuffer(int bufferIndex, int div)
{
	glVertexArrayBindingDivisor(vaoId, bufferIndex, div);
}

void VertexArrayObject::BindAttribDivisor(int attribIndex, int div)
{
	glVertexAttribDivisor(attribIndex, div);
}

void VertexArrayObject::BindElementBuffer(me::render::object::Buffer* elementBuffer)
{
	glVertexArrayElementBuffer(vaoId, elementBuffer->GetBuffer());
}
