#pragma once

#include <SDL.h>
#include <chrono>

#include <Windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

class OpenGLRenderer
{
private:
	SDL_Surface*    Surf_Display;
	int m_w;
	int m_h;
	int m_z;

	int fps_c;
	long fps_s;
private:
	long getSystemCurrTimeMillis();
public:
	OpenGLRenderer();

	bool init(int w, int h, int zoom);

	void startRender();
	void endRender();

	void fpsTick();

	void cleanup();
};

