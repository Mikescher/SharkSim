#include "stdafx.h"

#include "WatorApp.h"

WatorApp::WatorApp() {
    Surf_Display = NULL;

    Running = true;
}

int WatorApp::OnExecute() {
    if(OnInit() == false) {
        return -1;
    }

    SDL_Event Event;

    while(Running) {
        while(SDL_PollEvent(&Event)) {
            OnEvent(&Event);
        }

        OnLoop();
        OnRender();
    }

    OnCleanup();

    return 0;
}

bool WatorApp::OnInit() {
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

    if((Surf_Display = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_GL_DOUBLEBUFFER | SDL_OPENGL)) == NULL) {
        return false;
    }

    glClearColor(0, 0, 0, 0);

    glViewport(0, 0, 640, 480);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0, 640, 480, 0, 1, 0);
    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);

    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_POINT_SMOOTH);

    glLoadIdentity();

    return true;
}

void WatorApp::OnLoop() {
}

void WatorApp::OnRender() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(10, 10, 0);

    glPointSize(1.0);

    glBegin(GL_POINTS);
        glColor3f(1, 1, 1); glVertex3f(14.5, 14.5, 0);
	glEnd();

    SDL_GL_SwapBuffers();
}

void WatorApp::OnEvent(SDL_Event* Event) {
    if(Event->type == SDL_QUIT) {
        Running = false;
    }
}

void WatorApp::OnCleanup() {
    SDL_FreeSurface(Surf_Display);
    SDL_Quit();
}