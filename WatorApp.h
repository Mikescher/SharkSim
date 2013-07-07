#include <stdlib.h>

#include "OpenGLRenderer.h"
#include "WatorMap.h"

#include <SDL.h>

#include <Windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

const int SIM_SPEED = 0;

const int MAP_WIDTH = 100;
const int MAP_HEIGHT = 100;
const int MAP_ZOOM = 1;

const int FISH_BREEDTIME = 3;
const int SHARK_BREEDTIME = 10;
const int SHARK_STARVETIME = 3;

class WatorApp {
private:
	OpenGLRenderer *renderer;
	WatorMap *map;

	bool Running;
public:
	WatorApp();
	int OnExecute();
public:
	void OnEvent(SDL_Event* Event);
	void render();
};