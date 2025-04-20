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

void Game::handleInput() {

	int keyPressed = GetKeyPressed();

	switch (keyPressed) {
	case KEY_LEFT:
		moveBlockLeft();
		break;
	case KEY_RIGHT:
		moveBlockRight();
		break;
	case KEY_DOWN:
		moveBlockDown();
		break;
	case KEY_UP:
		RotateBlock();
		break;
	}
}

void Game::moveBlockLeft() {

	currentBlock.Move(0, -1);
	if (isBlockOutside())
		currentBlock.Move(0, 1);
}

void Game::moveBlockRight() {

	currentBlock.Move(0, 1);
	if (isBlockOutside())
		currentBlock.Move(0, -1);
}

void Game::moveBlockDown() {

	currentBlock.Move(1, 0);
	if (isBlockOutside())
		currentBlock.Move(-1, 0);
}

bool Game::isBlockOutside() {

	std::vector<Position> tiles = currentBlock.getCellPositions();
	for (Position item : tiles)
		if (grid.isCellOutside(item.row, item.column))
			return true;
	return false;
}

void Game::RotateBlock() {

	currentBlock.Rotate();
}