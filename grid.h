#pragma once
#include <vector>
#include "raylib.h"

class Grid {

public:

	Grid();
	int grid[20][10];
	void Initialize();
	void Print();
	void Draw();

private:

	std::vector<Color> getCellColor();
	int numRows;
	int numCols;
	int cellSize;
	std::vector<Color> colors;
};