#include "VertexBufferObject.h"

VertexBufferObject::VertexBufferObject(const void* data, unsigned int size)
{
	glGenBuffers(1, &m_Id);
	this->Bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBufferObject::~VertexBufferObject()
{
	this->Delete();
}

void VertexBufferObject::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_Id);
}

void VertexBufferObject::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferObject::Delete() const
{
	glDeleteBuffers(1, &m_Id);
}
