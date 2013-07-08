#include "stdafx.h"
#include "OGLGraph.h"

OGLGraph::OGLGraph(int max, int height, double distance, Color color, int maxval)
{
	m_max = max;
	m_height = height;
	m_distance = distance;
	m_color = color;
	m_maxval = maxval;
}

OGLGraph::~OGLGraph(void)
{

}


void OGLGraph::render(int x, int y) {
	//###########
	glLineWidth(3.0);
	glColor3f(0, 0, 0);

	//###########
	glBegin(GL_LINE_STRIP);
	glVertex3f(x, y - m_height, 0);
	glVertex3f(x, y, 0);
	glVertex3f(x + m_maxval * m_distance, y, 0);
	glEnd();

	//###########
	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < values.size(); i++)
		glVertex3f(x + i * m_distance, y - (values.at(i) / (m_max * 1.0)) * m_height, 0);
	glEnd();

	//########################################################################################
	glColor3f(m_color.r, m_color.g, m_color.b);
	glLineWidth(1.0);

	//###########
	glLineWidth(1.0);

	glBegin(GL_LINE_STRIP);
	for (int i = 0; i < values.size(); i++)
		glVertex3f(x + i * m_distance, y - (values.at(i) / (m_max * 1.0)) * m_height, 0);
	glEnd();
}


void OGLGraph::addValue(int v) {
	values.push_back(v);
	if (values.size() > m_maxval) {
		values.erase(values.begin());
	}
}
