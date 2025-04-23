#pragma once
#include "grid.h"
#include "blocks.cpp"

class Game {
public:
	Game();
	~Game();
	void Draw();
	void handleInput();
	void moveBlockDown();
	bool gameOver;
	int score;
	Music music;

private: 
	bool isBlockOutside();
	void moveBlockLeft();
	void moveBlockRight();
	void RotateBlock();
	void lockBlock();
	bool blockFits();
	void Reset();
	void updateScore(int linesCleared, int moveDownPoints);
	Block getRandomBlock();
	Grid grid;
	std::vector<Block> getAllBlocks();
	std::vector<Block> blocks;
	Block currentBlock;
	Block nextBlock;
	Sound rotateSound;
	Sound clearSound;
};