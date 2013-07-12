#include "stdafx.h"

#include "WatorApp.h"

WatorApp::WatorApp() {
    Running = true;

	printSettings();
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

		if (GetAsyncKeyState(VK_RETURN)) map->resetMap();
		if (! GetAsyncKeyState(VK_SPACE) || (GetAsyncKeyState(VK_RIGHT) && ! wasLeftKeyPressed)) map->doThreadedTick();

		wasLeftKeyPressed = GetAsyncKeyState(VK_RIGHT) != 0; 

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

	if (GetAsyncKeyState(VK_TAB))
		map->renderGraphs();
}

void WatorApp::OnEvent(SDL_Event* Event) {
    if(Event->type == SDL_QUIT) {
        Running = false;
	}
}

void WatorApp::printSettings() {
	cout << "SharkSim (www.mikescher.de)" << endl;
	cout << endl;
	cout << "SHOW GRAPH: " << ((IS_SHOW_GRAPH) ? ("true") : ("false")) << endl;
	cout << "Simulation Speed: " << SIM_SPEED << "ms" << endl;
	cout << "ThreadCount: " << THREADCOUNT << "+1" << endl;
	cout << "Map Dimension: " << MAP_WIDTH << " x " << MAP_HEIGHT << endl;
	cout << "Map Zoom: " << MAP_ZOOM << "x" << endl;
	cout << endl;
	cout << "[FISH] BreedTime: " << FISH_BREEDTIME << endl;
	cout << "[FISH] Initial Percentage: " << PERC_FISH/100.0 << "%" << endl;
	cout << "[SHARK] BreedTime: " << SHARK_BREEDTIME << endl;
	cout << "[SHARK] StarveTime: " << SHARK_STARVETIME << endl;
	cout << "[SHARK] InitialPercentage: " << PERC_SHARK/100.0 << "%" << endl;
	cout << endl;
	cout << "Color Water: (" << COLOR_WATER.r << ", " << COLOR_WATER.g << ", " << COLOR_WATER.b << ")"  << endl;
	cout << "Color Fish: (" << COLOR_FISH.r << ", " << COLOR_FISH.g << ", " << COLOR_FISH.b << ")"  << endl;
	cout << "Color Shark: (" << COLOR_SHARK.r << ", " << COLOR_SHARK.g << ", " << COLOR_SHARK.b << ")"  << endl;
	cout << endl;
	cout << endl;
	cout << endl;
}