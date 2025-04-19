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
private: 
	std::vector<Block> blocks;
	Block currentBlock;
	Block nextBlock;
};