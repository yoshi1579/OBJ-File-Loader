#include "Mesh2.h"
#include "obj_loader.h"
#include <vector>
#include <GL\glew.h>

using namespace std;

Mesh::Mesh(const string& fileName)
{
	IndexedModel model = OBJModel(fileName).ToIndexedModel();

	initMesh(model);
}

Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int * indices, unsigned int numIndices)
{
	IndexedModel model;

	for (unsigned int i = 0; i < numVertices; i++)
	{
		model.positions.push_back(*vertices[i].GetPos());
		model.texCoords.push_back(*vertices[i].GetTexCoord());
	}

	for (unsigned int i = 0; i < numIndices; i++)
		model.indices.push_back(indices[i]);

	initMesh(model);
	/*
	//draw_count = numVertices;
	draw_count = numIndices;

	glGenVertexArrays(1, &m_glVertexArrayObject);

	// connect the name returned from glGenVertexArrays to array object
	glBindVertexArray(m_glVertexArrayObject);

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


	// create space for buffers
	glGenBuffers(NUM_BUFFER, m_glVertexArrayBuffers);
	// bind buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_glVertexArrayBuffers[POSITION_VB]);
	// write data to the buffer
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);

	// tell open GL how to read vertex array
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// texture coordinate
	// bind buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_glVertexArrayBuffers[TEXCOORD_VB]);
	// write data to the buffer
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(texCoords[0]), &texCoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);

	// tell open GL how to read vertex array
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	// bind indices array
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_glVertexArrayBuffers[INDEX_VB]);
	// write data to the buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numVertices * sizeof(indices[0]), &indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
	*/
}

void Mesh::Draw()
{
	glBindVertexArray(m_glVertexArrayObject);

	glDrawElements(GL_TRIANGLES, draw_count, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &m_glVertexArrayObject);
}

void Mesh::initMesh(const IndexedModel & model)
{
	
	//draw_count = numVertices;
	draw_count = model.indices.size();

	glGenVertexArrays(1, &m_glVertexArrayObject);

	// connect the name returned from glGenVertexArrays to array object
	glBindVertexArray(m_glVertexArrayObject);

	// create space for buffers
	glGenBuffers(NUM_BUFFER, m_glVertexArrayBuffers);
	// bind buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_glVertexArrayBuffers[POSITION_VB]);
	// write data to the buffer
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);

	// tell open GL how to read vertex array
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// texture coordinate
	// bind buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_glVertexArrayBuffers[TEXCOORD_VB]);
	// write data to the buffer
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);

	// tell open GL how to read vertex array
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);


	// bind indices array
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_glVertexArrayBuffers[INDEX_VB]);
	// write data to the buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
	
}
