#ifndef MESH_H
#define MESH_H

#include <glm/glm/glm.hpp>
#include <GL/glew.h>

class Vertex
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord)
	{
		this->pos = pos;
		this->texCoord = texCoord;
	}

	inline glm::vec3* GetPos() { return &pos; }
	inline glm::vec2* GetTexCoord() { return &texCoord; }

private:
	// position of vertex
	glm::vec3 pos;
	// position of a texture mapping to the coordinate
	glm::vec2 texCoord;
};



class Mesh
{
public:
	Mesh(Vertex* vertices, unsigned int numVertices);
	void Draw();
	~Mesh();

private:
	Mesh(const Mesh& other){}
	void operator= (const Mesh& other){}

	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		NUM_BUFFERS
	};

	// this reffering to mesh data on GPU
	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	// how many things need to be drawed
	unsigned int m_drawCount;
};

#endif // !MESH_H
