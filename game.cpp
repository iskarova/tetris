#include "game.h"
#include <random>

Game::Game() {

	grid = Grid();
	blocks = getAllBlocks();
	currentBlock = getRandomBlock();
	nextBlock = getRandomBlock();
}

Block Game::getRandomBlock() {

	if (blocks.empty()) {
		blocks = getAllBlocks();
	}
	int index = rand() % blocks.size();
	Block block = blocks[index];
	blocks.erase(blocks.begin() + index);
	return block;
}

std::vector<Block> Game::getAllBlocks() {
	return { IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock() };
}

void Game::Draw() {

	grid.Draw();
	currentBlock.Draw();
}