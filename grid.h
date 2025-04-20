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
	bool isCellOutside(int row, int column);
	bool isCellEmpty(int row, int column);

private:

	int numRows;
	int numCols;
	int cellSize;
	std::vector<Color> colors;
};