#include "game.h"
#include <random>

Game::Game() {

	grid = Grid();
	blocks = getAllBlocks();
	currentBlock = getRandomBlock();
	nextBlock = getRandomBlock();
	gameOver = false;
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

	if (!gameOver) {
		currentBlock.Move(0, -1);
		if (isBlockOutside() || blockFits() == false)
			currentBlock.Move(0, 1);
	}
}

void Game::moveBlockRight() {

	if (!gameOver) {
		currentBlock.Move(0, 1);
		if (isBlockOutside() || blockFits() == false)
			currentBlock.Move(0, -1);
	}
}

void Game::moveBlockDown() {

	if (!gameOver) {
		currentBlock.Move(1, 0);
		if (isBlockOutside() || blockFits() == false) {
			currentBlock.Move(-1, 0);
			lockBlock();
		}
	}
}

bool Game::isBlockOutside() {

	std::vector<Position> tiles = currentBlock.getCellPositions();
	for (Position item : tiles)
		if (grid.isCellOutside(item.row, item.column))
			return true;
	return false;
}

void Game::RotateBlock() {

	if (!gameOver) {
		currentBlock.Rotate();

		if (isBlockOutside() || blockFits() == false) currentBlock.undoRotation();
	}
}

void Game::lockBlock() {

	std::vector<Position> tiles = currentBlock.getCellPositions();
	for (Position item : tiles) {
		grid.grid[item.row][item.column] = currentBlock.id;
	}
	currentBlock = nextBlock;
	if (blockFits() == false) {
		gameOver = true;
	}
	nextBlock = getRandomBlock();
	grid.clearFullRows();
}

bool Game::blockFits()
{
	std::vector<Position> tiles = currentBlock.getCellPositions();
	for (Position item : tiles)
		if (grid.isCellEmpty(item.row, item.column) == false)
			return false;
	return true;
}
