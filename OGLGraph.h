#pragma once

#include <vector>
#include <SDL.h>

#include <Windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

#include "Color.h"

class OGLGraph
{
private:
	std::vector<int> values;

	int m_max;
	int m_height;
	double m_distance;
	Color m_color;
	int m_maxval;
public:
	OGLGraph(int max, int height, double distance, Color color, int maxval);
	~OGLGraph(void);

	void render(int x, int y);

	void addValue(int v);
};

