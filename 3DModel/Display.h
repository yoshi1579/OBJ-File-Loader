#include <SDL/SDL.h>
#include <iostream>
#include <string>

#ifndef DISPLAY_H
#define DISPLAY_H

using namespace std;

class Display
{
public:
	Display(int width, int height, const string& title);
	void Update();
	bool IsClosed();
	void Clear(float r, float g, float b, float a);
	virtual ~Display();
private:
	Display(const Display& other){}
	Display operator =(const Display& other){}

	SDL_Window* m_window;
	SDL_GLContext m_glContext;
	bool m_isClosed;
};
#endif
