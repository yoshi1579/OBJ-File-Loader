#ifndef WINDOW_H
#define WINDOW_H



#include<iostream>
#include <string.h>
#include <SDL\SDL.h>

using namespace std;

class Window
{
public:
	Window(int width, int height, const string title);
	
	bool GetbClosed();
	void SwapBuffer();
	~Window();


private:
	SDL_Window* window;
	SDL_GLContext glContext;
	bool bClosed;
};

#endif // !WINDOW_H