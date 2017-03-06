#ifndef SHADER_H 
#define SHADER_H

#include <string>
#include <GL/glew.h>
#include "transform.h"
using namespace std;

class Shader
{
public:
	Shader(const string& fileName);
	void Bind();
	void Update(const Transform& transform);
	virtual ~Shader();
protected:
private:
	Shader(const Shader& other){}
	Shader& operator = (const Shader& other){}

	enum
	{
		TRANSFORM_U,

		NUM_UNIFORMS
	};

	// the number of shader 
	static const unsigned int NUM_SHADER = 2;
	// GL keep track of where the program is 
	GLuint m_program;
	// fragment shader and vertex shader not including geometory shader
	GLuint m_shaders[NUM_SHADER];

	GLuint m_uniforms[NUM_UNIFORMS];
};

#endif // !1
