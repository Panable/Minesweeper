#ifndef INDEX_BUFFER_OBJECT_CLASS
#define INDEX_BUFFER_OBJECT_CLASS
#include <glad/glad.h>
class IndexBufferObject
{
public:
	unsigned int m_Id;
private:
	void Delete() const;
public:
	IndexBufferObject(const void* data, unsigned int size);
	~IndexBufferObject();
	void Bind() const;
	void Unbind() const;
};
#endif
