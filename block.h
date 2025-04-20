#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "colors.h"

class Block {
public:
	Block();
	//void Draw(int offsetX, int offsetY);
	void Draw();
	void Move(int rows, int columns);
	void Rotate();
	std::vector<Position> getCellPositions();
	int id;
	std::map<int, std::vector<Position>> cells;
private:
	int cellSize;
	int rotationState;
	std::vector<Color> colors;
	int rowOffset;
	int columnOffset;
};