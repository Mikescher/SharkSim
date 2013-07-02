#include <stdlib.h>

#include <SDL.h>

#include <Windows.h>
#include <gl/gl.h>
#include <gl/glu.h>


class WatorApp {
private:
	bool            Running;
	SDL_Surface*    Surf_Display;
public:
	WatorApp();
	int OnExecute();
public:
	bool OnInit();
	void OnEvent(SDL_Event* Event);
	void OnLoop();
	void OnRender();
	void OnCleanup();
};