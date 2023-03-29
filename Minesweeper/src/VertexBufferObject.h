#ifndef VERTEX_BUFFER_OBJECT_CLASS
#define VERTEX_BUFFER_OBJECT_CLASS
#include<glad/glad.h>

class VertexBufferObject
{
public:
	unsigned int m_Id;
public:
	VertexBufferObject(const void* data, unsigned int size);
	~VertexBufferObject();
	void Bind() const;
	void Unbind() const;
private:
	void Delete() const;
};


#endif
