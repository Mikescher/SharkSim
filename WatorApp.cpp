#include "stdafx.h"

#include "WatorApp.h"

WatorApp::WatorApp() {
    Running = true;
}

int WatorApp::OnExecute() {
	renderer = new OpenGLRenderer();
	map = new WatorMap(MAP_WIDTH, MAP_HEIGHT);

	if(! renderer->init(MAP_WIDTH, MAP_HEIGHT, MAP_ZOOM)) {
        return -1;
    }

    SDL_Event Event;

    while(Running) {
        while(SDL_PollEvent(&Event)) {
            OnEvent(&Event);
        }

		map->doTick(FISH_BREEDTIME, SHARK_BREEDTIME, SHARK_STARVETIME);

		renderer->startRender();
		render();
		renderer->endRender();

		renderer->fpsTick();

		if (SIM_SPEED > 0) Sleep(SIM_SPEED);
    }

	renderer->cleanup();

    return 0;
}

void WatorApp::render() {
    glBegin(GL_POINTS);

	for (int x = 0; x < MAP_WIDTH; x++) {
		for (int y= 0; y < MAP_HEIGHT; y++) {
			switch(map->getCellType(x, y)) {
			case WCT_FISH:
				glColor3f(0, 1, 0);
				break;
			case WCT_FREE:
				glColor3f(0, 0, 1);
				break;
			case WCT_SHARK:
				glColor3f(0, 0, 0);
				break;
			}
			glVertex3f(x + 0.5, y + 0.5, 0);
		}
	}

	glEnd();
}

void WatorApp::OnEvent(SDL_Event* Event) {
    if(Event->type == SDL_QUIT) {
        Running = false;
    }
}
