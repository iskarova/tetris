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
	int clearFullRows();

private:
	bool isRowFull(int row);
	void clearRow(int row);
	void moveRowDown(int row, int numRows);
	int numRows;
	int numCols;
	int cellSize;
	std::vector<Color> colors;
};