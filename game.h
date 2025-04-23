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
private: 
	bool isBlockOutside();
	void RotateBlock();
	void lockBlock();
	bool blockFits();
	std::vector<Block> blocks;
	Block currentBlock;
	Block nextBlock;
};