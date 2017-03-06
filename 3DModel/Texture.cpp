#include "Texture.h"
#include "stb_image.h"
#include <cassert>
#include <iostream>
using namespace std;

Texture::Texture(const string& fileName)
{
	int width, height, numComponets;
	
	// loading stb image
	unsigned char* imageData = stbi_load(fileName.c_str(), &width, &height, &numComponets, 4);
	if (imageData == NULL)
	{
		cerr << "Texture loading fail: " << fileName << endl;
	}

	// generate 1 texture space in GPU
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	//Control texture wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	stbi_image_free(imageData);

}

Texture::~Texture()
{
	glDeleteTextures(1, &m_texture);
}

void Texture::Bind(unsigned int unit)
{
	assert(unit >= 0, unit <= 31);

	// set which texture you are working with
	glActiveTexture(GL_TEXTURE + unit);
	// binding texture
	glBindTexture(GL_TEXTURE_2D, m_texture);
}