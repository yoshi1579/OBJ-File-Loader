#ifndef  TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/glew.h>
using namespace std;

class Texture
{
public:
	Texture(const string& fileName);
	// set openGL to start using whatever texture, unit is how many textures I want to bind
	void Bind(unsigned int uint);

	virtual ~Texture();
private:
	Texture (const Texture& other){}
	void operator =(const Texture&other){}

	GLuint m_texture;
};
#endif // ! TECTURE_H

