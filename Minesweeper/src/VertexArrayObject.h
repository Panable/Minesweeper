#ifndef VERTEX_ARRAY_OBJECT_CLASS
#define VERTEX_ARRAY_OBJECT_CLASS
#include "VertexBufferObject.h"

class VertexArrayObject
{
public:
	unsigned int m_Id;
	VertexArrayObject();
	~VertexArrayObject();
private:
	void Delete() const;
public:
	void Bind() const;
	void Unbind() const;
	void LinkAttrib(const VertexBufferObject& VBO, const unsigned int index, const unsigned int numElements, GLenum type, const unsigned int stride, const void* offset) const;
};
#endif
