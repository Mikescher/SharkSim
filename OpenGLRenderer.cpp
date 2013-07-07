#include "stdafx.h"
#include "OpenGLRenderer.h"

OpenGLRenderer::OpenGLRenderer() {
	fps_c = 0;
	fps_s = getSystemCurrTimeMillis();
}

bool OpenGLRenderer::init(int w, int h, int z) {
	m_w = w;
	m_h = h;
	m_z = z;

	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		return false;
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,    	    8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,  	    8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,   	    8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,  	    8);

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,  	    16);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,		    32);

	SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,	    8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,	8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,	    8);
	SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,	8);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  1);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  2);

	if((Surf_Display = SDL_SetVideoMode(w * z, h * z, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL)) == NULL) {
		return false;
	}

	glClearColor(0, 0, 0, 0);

	glViewport(0, 0, w * z, h * z);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, w, h, 0, 1, 0);
	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);

	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_POINT_SMOOTH);

	glLoadIdentity();

	return true;
}

void OpenGLRenderer::startRender() {
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	glPointSize(1.0 * m_z);
}

void OpenGLRenderer::endRender() {
	SDL_GL_SwapBuffers();
}

void OpenGLRenderer::cleanup() {
	SDL_FreeSurface(Surf_Display);
	SDL_Quit();
}

long OpenGLRenderer::getSystemCurrTimeMillis() {
	auto time = std::chrono::system_clock::now();

	auto since_epoch = time.time_since_epoch(); 

	auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(since_epoch);

	return (long) millis.count(); 
}

void OpenGLRenderer::fpsTick() {
	long delta = getSystemCurrTimeMillis() - fps_s;
	if (delta > 5000) {
		double fps = fps_c / 5.0;
		printf("FPS: %.1f\n", fps);
		fps_c = 0;
		fps_s += 5000;
	}

	fps_c++;
}