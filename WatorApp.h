#include <stdlib.h>

#include "OpenGLRenderer.h"
#include "WatorMap.h"

#include <SDL.h>

#include <Windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "const.h"

class WatorApp {
private:
	OpenGLRenderer *renderer;
	WatorMap *map;

	bool wasLeftKeyPressed;

	bool Running;
public:
	WatorApp();
	int OnExecute();
public:
	void OnEvent(SDL_Event* Event);
	void render();
};