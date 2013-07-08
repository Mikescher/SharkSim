#include "stdafx.h"

#include "WatorApp.h"

WatorApp::WatorApp() {
    Running = true;
}

int WatorApp::OnExecute() {
	renderer = new OpenGLRenderer();
	map = new WatorMap(MAP_WIDTH, MAP_HEIGHT, FISH_BREEDTIME, SHARK_BREEDTIME, SHARK_STARVETIME, THREADCOUNT);

	if(! renderer->init(MAP_WIDTH, MAP_HEIGHT, MAP_ZOOM)) {
        return -1;
    }

    SDL_Event Event;

    while(Running) {
        while(SDL_PollEvent(&Event)) {
            OnEvent(&Event);
        }

		map->doThreadedTick();

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
	glClearColor(COLOR_WATER.r, COLOR_WATER.g, COLOR_WATER.b, 0);

    glBegin(GL_POINTS);

	for (int x = 0; x < MAP_WIDTH; x++) {
		for (int y= 0; y < MAP_HEIGHT; y++) {
			switch(map->getCellType(x, y)) {
			case WCT_FISH:
				glColor3f(COLOR_FISH.r, COLOR_FISH.g, COLOR_FISH.b);
				glVertex3f(x + 0.5, y + 0.5, 0);
				break;
			case WCT_SHARK:
				glColor3f(COLOR_SHARK.r, COLOR_SHARK.g, COLOR_SHARK.b);
				glVertex3f(x + 0.5, y + 0.5, 0);
				break;
			}
		}
	}
	 
	glEnd();

	map->renderGraphs();
}

void WatorApp::OnEvent(SDL_Event* Event) {
    if(Event->type == SDL_QUIT) {
        Running = false;
    }
}
