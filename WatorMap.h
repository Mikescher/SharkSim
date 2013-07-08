#pragma once

#include <stdlib.h>
#include <ctime>
#include <vector>

#include <boost\thread.hpp>
#include <boost\thread\barrier.hpp>
#include <boost\bind.hpp>

#include "Dynamic2DArray.h"

enum WatorCellType {WCT_FREE, WCT_SHARK, WCT_FISH};

struct WatorCell {
	int lastModifiedZyklus; // Dont do a Cell two times (again after moving ...)

	WatorCellType type;
	int lifeTime;
	int eatTime; // Only for Sharks
};

struct Color {
	double r;
	double g;
	double b;
};

class WatorMap
{
private:
	int m_currZyklus;

	int m_width;
	int m_height;

	int m_fishBreedTime;
	int m_sharkBreedTime;
	int m_sharkStarveTime;

	WatorCell **map;
	std::vector<boost::thread*> m_threadlist;
	boost::barrier *m_barrier;
private:
	void createMap();
	void initThreads(int threads);

	void moveCell(int fx, int fy, int tx, int ty);
	void clearCell(int x, int y);

	void moveFishRandom(int x, int y);
	void breedFish(int x, int y);

	void moveSharkRandom(int x, int y);
	void breedShark(int x, int y);

	int getXForDirection(int direc);
	int getYForDirection(int direc);
public:
	WatorMap(int width, int height, int fbt, int sbt, int sst, int threadcount);
	~WatorMap(void);

	void doThreadedTick();
	void doTick(boost::barrier *barrier, int startY, int endY);

	WatorCell* getCell(int x, int y);
	WatorCellType getCellType(int x, int y);
	bool isCellFree(int x, int y);

	int getWidth();
	int getHeight();
};

