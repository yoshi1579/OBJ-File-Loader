#ifndef SHADER2_H
#define SHADER2_H

#include <iostream>
#include <string.h>
#include <GL\glew.h>
#include "transform.h"
#include "camera.h"

using namespace std;
class Shader
{
public:
	Shader(const string fileName);
	~Shader();
	void Bind();

	void Update(const Transform& transform, const Camera& camera);

private:
	static const unsigned int NUM_SHADER = 2;

	enum
	{
		TRANSFORM_U,
		NUM_UNIFORMS
	};

	GLuint glProgram;
	GLuint shaders[NUM_SHADER];
	GLuint m_uniforms[NUM_UNIFORMS];

	
};

#endif // !SHADER2_H
