#pragma once

enum WatorCellType {WCT_FREE, WCT_SHARK, WCT_FISH};

struct WatorCell {
	WatorCellType type;
	int energy; // Energy for Sharks or Lifetime for Fishes
};

class WatorMap
{
private:
	int m_width;
	int m_height;

	WatorCell **map;
private:
	void createMap();
public:
	WatorMap(int width, int height);
	~WatorMap(void);

	int getWidth();
	int getHeight();
};

