#include "VertexArray.h"
#include <GL/glew.h>

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray()
{

}

void VertexArray::AddBuffer(const VertexBuffer & buffer, const VertexBufferLayout& layout)
{
	Bind();

	buffer.Bind();

	const auto& elements = layout.GetElements();
	unsigned int offset = 0;

	 for (unsigned int i = 0; i < elements.size(); ++i)
	 {
		 const auto element = elements[i];
		 glEnableVertexAttribArray(i);
		 glVertexAttribPointer(i, element.count, element.type,
			 element.normalize ? GL_TRUE : GL_FALSE, layout.GetStride(), (const void *)offset);
		 offset += element.count * VertexBufferElement::GetStrideByte(element.type);
	 }
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
