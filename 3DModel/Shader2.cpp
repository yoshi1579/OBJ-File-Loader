#include "Shader2.h"
#include <fstream>
#include <iostream>
#include <string>

static void ShaderErrorCheck(GLuint shader, GLuint flag, bool isProgram, const string& errorMassage);
static string LoadFile(const string & fileName);
static GLuint CreateShader(const string& text, GLenum shaderType);

using namespace std;

Shader::Shader(const string fileName)
{
	// create empty project that shaders can be attached 
	glProgram = glCreateProgram();

	if (glProgram == 0)
	{
		cerr << "Error: failed to create gl empty project\n";
	}

	// load shader source file
	string sourceFileVS = LoadFile(fileName + ".vs.txt");
	string sourceFileFS = LoadFile(fileName + ".fs.txt");

	// create shader object and compile
	shaders[0] = CreateShader(sourceFileVS, GL_VERTEX_SHADER);
	shaders[1] = CreateShader(sourceFileFS, GL_FRAGMENT_SHADER);

	for (int i = 0; i < NUM_SHADER; i++)
	{
		glAttachShader(glProgram, shaders[i]);
	}

	glBindAttribLocation(glProgram, 0, "position");
	// send texCoord in mesh to vertex shader
	glBindAttribLocation(glProgram, 1, "texCoord");

	// link shaders
	glLinkProgram(glProgram);
	ShaderErrorCheck(glProgram, GL_LINK_STATUS, true, "Link Error");

	// validate 
	glValidateProgram(glProgram);
	ShaderErrorCheck(glProgram, GL_VALIDATE_STATUS, true, "Validation Error");

	// get uniform variable in shader
	m_uniforms[TRANSFORM_U] = glGetUniformLocation(glProgram, "transform");
}

Shader::~Shader()
{
	for (int i = 0; i < NUM_SHADER; i++)
	{
		// detach shaders
		glDetachShader(glProgram, shaders[i]);

		// delete shaders
		glDeleteShader(shaders[i]);
	}
	// delete gl program
	glDeleteProgram(glProgram);
}

void Shader::Bind()
{
	glUseProgram(glProgram);
}

void Shader::Update(const Transform & transform, const Camera& camera)
{
	glm::mat4 model = camera.GetViewProjection() * transform.GetModel();
	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
}

// take shader source file and compile it. return shader compiled object
static GLuint CreateShader(const string& fileName, GLenum shaderType)
{
	// create an empty shader object 
	GLuint shader = glCreateShader(shaderType);
	if (shader == 0)
	{
		cerr << "Error: falied to create shader object\n";
	}

	const GLchar * shaderSource[1]; 
	GLint sourceLength[1];

	shaderSource[0] = fileName.c_str();
	sourceLength[0] = fileName.length();

	// set source code 
	glShaderSource(shader, 1, shaderSource, sourceLength);

	// compile shader
	glCompileShader(shader);

	// error checking for compiling a shader
	ShaderErrorCheck(shader, GL_COMPILE_STATUS, false, "Shader compile Error");

	return shader;
}

// load shader files
static string LoadFile(const string& fileName)
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

// error checking for creating shaders
static void ShaderErrorCheck(GLuint program, GLuint flag, bool isProgram, const string& massage)
{
	GLint param = 0;
	GLsizei* length = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)	// error checking for gl Program
	{
		glGetProgramiv(program, flag, &param);
	}
	else			// error checking for shader
	{
		glGetShaderiv(program, flag, &param);
	}

	if (param == GL_FALSE)	// if an error occurs, show the Info log
	{
		if (isProgram)
			glGetProgramInfoLog(program, sizeof(error), length, error);
		else
			glGetShaderInfoLog(program, sizeof(error), length, error);

		cerr << massage << ": " << error << endl;
	}
}