#include "VertexArrayObject.h"

VertexArrayObject::VertexArrayObject()
{
	glGenVertexArrays(1, &m_Id);
}

VertexArrayObject::~VertexArrayObject()
{
	this->Delete();
}

void VertexArrayObject::Delete() const
{
	glDeleteVertexArrays(1, &m_Id);
}

void VertexArrayObject::Bind() const
{
	glBindVertexArray(m_Id);
}

void VertexArrayObject::Unbind() const
{
	glBindVertexArray(0);
}

void VertexArrayObject::LinkAttrib(const VertexBufferObject& VBO, const unsigned index, const unsigned numElements, const GLenum type,
                                   const unsigned stride, const void* offset) const
{
	VBO.Bind();
	glVertexAttribPointer(index, numElements, type, GL_FALSE, stride, offset);
	glEnableVertexAttribArray(index);
	VBO.Unbind();
}
