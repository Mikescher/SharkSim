#pragma once

#include "Color.h"

#define SHOW_GRAPH

const Color COLOR_GRAPHFISH = {1, 1, 1};
const Color COLOR_GRAPHSHARK = {1, 1, 1};

const int SIM_SPEED = 0;
const int THREADCOUNT = 8;

const int MAP_WIDTH = 600;
const int MAP_HEIGHT = 600;
const int MAP_ZOOM = 1;

const int FISH_BREEDTIME = 3;
const int SHARK_BREEDTIME = 10;
const int SHARK_STARVETIME = 3;

const int PERC_SHARK = 100; // 1/10 Promille
const int PERC_FISH = 1000;

const Color COLOR_WATER = {0, 0.835, 1};
const Color COLOR_FISH = {0, 1, 0.4};
const Color COLOR_SHARK = {1, 0, 0};