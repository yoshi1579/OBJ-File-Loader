#include "mesh.h"
#include <vector>
using namespace std;

Mesh::Mesh(Vertex* vertices, unsigned int numVertices)
{
	m_drawCount = numVertices;

	// generating a space for vertex array
	glGenVertexArrays(1, &m_vertexArrayObject);
	// now we bind vertex to be affected
	glBindVertexArray(m_vertexArrayObject);

	// making sequential array of data
	vector < glm::vec3> positions;
	vector < glm::vec2> texCoords;

	positions.reserve(numVertices);
	texCoords.reserve(numVertices);


	// putting each position and texCoord to separate vector
	for (int i = 0; i < numVertices; i++)
	{
		positions.push_back(*vertices[i].GetPos());
		texCoords.push_back(*vertices[i].GetTexCoord());
	}


	// get some buffers on GPU to write on
	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	// bind the buffer to write on and tell it how to interpret. this case array
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	// now put vertex data to array
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);
	// setup attrib Array (vec, color .. etc) this case just vec
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	

	// bind the buffer to write on and tell it how to interpret. this case array
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
	// now put vertex data to array
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);
	// setup attrib Array (vec, color .. etc) this case just vec
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// stop using vertex array
	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	// deleteing vertex array space
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::Draw()
{
	glBindVertexArray(m_vertexArrayObject);

	// tell how to draw
	glDrawArrays(GL_TRIANGLES, 0, m_drawCount);

	glBindVertexArray(0);
}