#include "stdafx.h"

#include "WatorMap.h"

WatorMap::WatorMap(int width, int height, int fbt, int sbt, int sst, int threadcount)
{
	srand((unsigned int) time(NULL));

	m_width = width;
	m_height = height;
	m_fishBreedTime = fbt;
	m_sharkBreedTime = sbt;
	m_sharkStarveTime = sst;
	m_currZyklus = 0;

	createMap();

	initThreads(threadcount);
}


WatorMap::~WatorMap(void)
{
	freeDynamicArray(map);
}

int WatorMap::getWidth() {
	return m_width;
}

int WatorMap::getHeight() {
	return m_height;
}

void WatorMap::createMap() {
	map = allocateDynamicArray<WatorCell>(m_width, m_height);

	for (int x = 0; x < m_width; x++) {
		for (int y= 0; y < m_height; y++) {
			map[x][y].lastModifiedZyklus = 0;

			map[x][y].eatTime = 0;
			map[x][y].lifeTime = 0;

			map[x][y].type = WCT_FREE;
			if (rand() % 10 == 1) map[x][y].type = WCT_FISH;
			if (rand() % 100 == 1) map[x][y].type = WCT_SHARK;
		}
	}
}

void WatorMap::initThreads(int threads) {
	m_barrier = new boost::barrier(threads + 1);

	int thread_height = m_height / threads;

	int start = 0;
	int end = 0;

	for (int i = 0; i < threads; i++) {
		start = end;
		end = end + thread_height;

		if (i+1 == threads) // last
			end = m_height;

		boost::thread *t = new boost::thread(&WatorMap::doTick, this, m_barrier, start, end);
		m_threadlist.push_back(t);
	}
}

void WatorMap::doThreadedTick() {
	m_currZyklus++;

	m_barrier->wait();
}

void WatorMap::doTick(boost::barrier *barrier, int startY, int endY) {
	for(;;) {

		for (int y = startY; y < endY; y++) {
			for (int x = 0; x < m_width; x++) {
				if (map[x][y].lastModifiedZyklus != m_currZyklus) {
					map[x][y].lastModifiedZyklus = m_currZyklus;

					switch(map[x][y].type) {
					case WCT_FISH:
						map[x][y].lifeTime = map[x][y].lifeTime + 1;
						if (map[x][y].lifeTime > m_fishBreedTime) breedFish(x, y);
						moveFishRandom(x, y);
						break;
					case WCT_SHARK:
						map[x][y].lifeTime++;
						map[x][y].eatTime++;

						if (map[x][y].lifeTime > m_sharkBreedTime) breedShark(x, y);
						if (map[x][y].eatTime > m_sharkStarveTime) {
							clearCell(x, y); // Starve
						} else {
							moveSharkRandom(x, y);
						}

						break;
					}
				}
			}
		}
		barrier->wait();
	}
}

WatorCell* WatorMap::getCell(int x, int y) {
	return &map[(x + m_width) % m_width][(y + m_height) % m_height];
}

WatorCellType WatorMap::getCellType(int x, int y) {
	return getCell(x, y)->type;
}

bool WatorMap::isCellFree(int x, int y) {
	return map[(x + m_width) % m_width][(y + m_height) % m_height].type == WCT_FREE;
}

void WatorMap::moveCell(int fx, int fy, int tx, int ty) {
	WatorCell* from = getCell(fx, fy);
	WatorCell* to = getCell(tx, ty);

	to->eatTime = from->eatTime;
	to->lifeTime = from->lifeTime;
	to->type = from->type;
	to->lastModifiedZyklus = from->lastModifiedZyklus;

	from->eatTime = 0;
	from->lifeTime = 0;
	from->type = WCT_FREE;
}

void WatorMap::clearCell(int x, int y) {
	WatorCell* c = getCell(x, y);
	c->eatTime = 0;
	c->lifeTime = 0;
	c->type = WCT_FREE;
}

void WatorMap::moveFishRandom(int x, int y) {
	int direction = rand() % 4;
	for (int i = 0; i < 4; i++) {
		if (isCellFree(x + getXForDirection(direction), y + getYForDirection(direction))) {
			moveCell(x, y, x + getXForDirection(direction), y + getYForDirection(direction));
			return;
		}

		direction = (direction+1) % 4;
	}
}

void WatorMap::breedFish(int x, int y) {
	int direction = rand() % 4;
	for (int i = 0; i < 4; i++) {
		if (isCellFree(x + getXForDirection(direction), y + getYForDirection(direction))) {
			WatorCell* newc = getCell(x + getXForDirection(direction), y + getYForDirection(direction));

			newc->type = WCT_FISH;
			newc->lastModifiedZyklus = m_currZyklus;
			newc->lifeTime = 0;

			getCell(x, y)->lifeTime = 0;
			return;
		}

		direction = (direction+1) % 4;
	}
}

void WatorMap::moveSharkRandom(int x, int y) {

	// SEARCH 4 FISH

	int direction = rand() % 4;
	for (int i = 0; i < 4; i++) {
		if (getCellType(x + getXForDirection(direction), y + getYForDirection(direction)) == WCT_FISH) {
			getCell(x, y)->eatTime = 0;
			moveCell(x, y, x + getXForDirection(direction), y + getYForDirection(direction));
			return;
		}

		direction = (direction+1) % 4;
	}

	// MOVE RANDOM
	for (int i = 0; i < 4; i++) {
		if (isCellFree(x + getXForDirection(direction), y + getYForDirection(direction))) {
			moveCell(x, y, x + getXForDirection(direction), y + getYForDirection(direction));
			return;
		}

		direction = (direction+1) % 4;
	}
}

void WatorMap::breedShark(int x, int y) {
	int direction = rand() % 4;
	for (int i = 0; i < 4; i++) {
		if (getCellType(x + getXForDirection(direction), y + getYForDirection(direction)) != WCT_SHARK) {
			WatorCell* newc = getCell(x + getXForDirection(direction), y + getYForDirection(direction));

			newc->type = WCT_SHARK;
			newc->lastModifiedZyklus = m_currZyklus;
			newc->lifeTime = 0;
			newc->eatTime = 0;

			getCell(x, y)->lifeTime = 0;
			return;
		}

		direction = (direction+1) % 4;
	}
}

int WatorMap::getXForDirection(int direc) {
	return (direc == 0 || direc == 2) ? (0) : ((direc == 1) ? (1) : (-1));  
}

int WatorMap::getYForDirection(int direc) {
	return (direc == 1 || direc == 3) ? (0) : ((direc == 0) ? (1) : (-1));  
}