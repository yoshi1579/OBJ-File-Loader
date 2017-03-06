#include "shader.h"
#include <fstream>
#include <iostream>
using namespace std;

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const string& errorMassage);
static string LoadShader(const string & fileName);
static GLuint CreateShader(const string& text, GLenum shaderType);

Shader::Shader(const string& fileName)
{
	// tell opengl that we created new shader program and openGL gives us a number to reference and space for it
	m_program = glCreateProgram();
	// assigning vertex shader, file extension .vs implies vertex shader personal convention to distinguish from fragment shader
	m_shaders[0] = CreateShader(LoadShader(fileName + ".vs.txt"), GL_VERTEX_SHADER);
	// fragment shader
	m_shaders[1] = CreateShader(LoadShader(fileName + ".fs.txt"), GL_FRAGMENT_SHADER);

	
	for (int i = 0; i < NUM_SHADER; i++)
	{
		// attach our shaders to m_program
		glAttachShader(m_program, m_shaders[i]);
	}

	// this tells openGL which part of data to read and what variables in shader programs
	glBindAttribLocation(m_program, 0, "position");

	// now we need to link the program and check if it's valid
	glLinkProgram(m_program);
	// this linking could fail, so need to check the error status
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error: Program linking failed: ");
	glValidateProgram(m_program);
	// the program could be invalid, so need to check the error status
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error: Program is invalid: ");

	// setting up transform uniform
	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
}

Shader::~Shader()
{
	// need to delete individual shaders
	for (int i = 0; i < NUM_SHADER; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}
	// delete the program 
	glDeleteProgram(m_program);
}

void Shader::Bind()
{
	glUseProgram(m_program);
}

// update transform
void Shader::Update(const Transform& transform)
{
	glm::mat4 model = transform.GetModel();
	glUniformMatrix4fv
}

// find error and display
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const string& errorMassage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
	{
		glGetProgramiv(shader, flag, &success);
	}
	else
	{
		glGetShaderiv(shader, flag, &success);
	}

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		cerr << errorMassage << ": '" << error << "'" << endl;
	}
}

// open file
static string LoadShader(const string & fileName)
{
	ifstream file;
	file.open((fileName).c_str());

	string output;
	string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");
		}
	}
	else
	{
		cerr << "Unable to load shader: " << fileName << endl;
	}
	return output;
}

static GLuint CreateShader(const string& text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	// error checking
	if (shader == 0)
	{
		cerr << "Error: Shader creation failed!" << endl;
	}

	// now take the input text and build shader and assign that to shader valuable
	// need to convert c++ string to c string
	const GLchar * shaderSourceStrings[1];
	GLint shaderSourceStringLength[1];

	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringLength[0] = text.length();

	// make GL compile the shader created
	glShaderSource(shader, 1, shaderSourceStrings, shaderSourceStringLength);
	glCompileShader(shader);

	// error checking for compilation
	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader Compilation failed: ");

	return shader;
}