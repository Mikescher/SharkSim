#pragma once

#include "Dynamic2DArray.h"
#include <stdlib.h>
#include <ctime>

enum WatorCellType {WCT_FREE, WCT_SHARK, WCT_FISH};

struct WatorCell {
	int lastModifiedZyklus; // Dont do a Cell two times (again after moving ...)

	WatorCellType type;
	int lifeTime;
	int eatTime; // Only for Sharks
};

class WatorMap
{
private:
	int m_currZyklus;

	int m_width;
	int m_height;

	WatorCell **map;
private:
	void createMap();

	void moveCell(int fx, int fy, int tx, int ty);
	void clearCell(int x, int y);

	void moveFishRandom(int x, int y);
	void breedFish(int x, int y);

	void moveSharkRandom(int x, int y);
	void breedShark(int x, int y);

	int getXForDirection(int direc);
	int getYForDirection(int direc);
public:
	WatorMap(int width, int height);
	~WatorMap(void);

	void doTick(int fishBreedTime, int sharkBreedTime, int sharkStarveTime);

	WatorCell* getCell(int x, int y);
	WatorCellType getCellType(int x, int y);
	bool isCellFree(int x, int y);

	int getWidth();
	int getHeight();
};

