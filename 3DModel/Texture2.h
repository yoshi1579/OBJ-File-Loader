#ifndef TEXTURE2_H
#define TEXTURE2_H

#include <iostream>
#include <string>
#include <GL\glew.h>

using namespace std;

class Texture
{
public:
	// takes file uploaded by stb_image
	Texture(const string& fileName);

	// unit: which texture to bind
	void Bind(unsigned int unit);

	~Texture();

private:

	// handle whatever handle openGL gives to us
	GLuint m_texture;
};

#endif // !TEXTURE2_H

