#pragma once
#include "grid.h"
#include "blocks.cpp"

class Game {
public:
	Game();
	Grid grid;
	Block getRandomBlock();
	std::vector<Block> getAllBlocks();
	void Draw();
	void handleInput();
	void moveBlockLeft();
	void moveBlockRight();
	void moveBlockDown();
	bool gameOver;
	int score;
private: 
	bool isBlockOutside();
	void RotateBlock();
	void lockBlock();
	bool blockFits();
	void Reset();
	void updateScore(int linesCleared, int moveDownPoints);
	std::vector<Block> blocks;
	Block currentBlock;
	Block nextBlock;
};