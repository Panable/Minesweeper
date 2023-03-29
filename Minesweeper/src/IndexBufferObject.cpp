#include "IndexBufferObject.h"

void IndexBufferObject::Delete() const
{
	glDeleteBuffers(1, &m_Id);
}

IndexBufferObject::IndexBufferObject(const void* data, unsigned size)
{
	glGenBuffers(1, &m_Id);
	this->Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

IndexBufferObject::~IndexBufferObject()
{
	this->Delete();
}

void IndexBufferObject::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id);
}

void IndexBufferObject::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
