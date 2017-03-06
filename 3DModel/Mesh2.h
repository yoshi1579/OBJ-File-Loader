#ifndef MESH2_H
#define MESH2_H

#include <glm\glm\glm.hpp>
#include <GL/glew.h>
#include <string>
#include "obj_loader.h"

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
	glm::vec3 pos;
	glm::vec2 texCoord;
};

class Mesh
{
public:
	Mesh(Vertex* vertices, unsigned int numVertices, unsigned int * indices, unsigned int numIndices);
	Mesh(const std::string & fileName);
	void Draw();
	~Mesh();
private:

	void initMesh(const IndexedModel& model);
	
	enum
	{
		POSITION_VB,
		TEXCOORD_VB,
		NORMAL_VB,
		INDEX_VB,
		NUM_BUFFER
	};

	// reference to vertex array object
	GLuint m_glVertexArrayObject;
	GLuint m_glVertexArrayBuffers[NUM_BUFFER];

	unsigned int draw_count;
};

#endif // !MESH2_H

