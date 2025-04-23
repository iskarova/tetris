#include "game.h"
#include <random>
#include <ctime>

Game::Game() {

	grid = Grid();
	blocks = getAllBlocks();
	currentBlock = getRandomBlock();
	nextBlock = getRandomBlock();
	gameOver = false;
	score = 0;
	InitAudioDevice();
	music = LoadMusicStream("sounds/electro.mp3");
	PlayMusicStream(music);
	rotateSound = LoadSound("sounds/beep-sound.mp3");
	clearSound = LoadSound("sounds/machine-brain.mp3");
}

Game::~Game(){

	UnloadSound(rotateSound);
	UnloadSound(clearSound);
	UnloadMusicStream(music);
	CloseAudioDevice();
}

Block Game::getRandomBlock() {

	if (blocks.empty()) {
		blocks = getAllBlocks();
	}
	srand((unsigned)time(0));
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
	currentBlock.Draw(11, 11);

	switch (nextBlock.id) {
		case 3:
			nextBlock.Draw(275, 290);
			break;
		case 4:
			nextBlock.Draw(275, 280);
			break;
		default:
			nextBlock.Draw(290, 275);
			break;
	}
}

void Game::handleInput() {

	int keyPressed = GetKeyPressed();

	if (gameOver && keyPressed != 0) {
		
		gameOver = false;
		Reset();
	}

	switch (keyPressed) {
	case KEY_LEFT:
		moveBlockLeft();
		break;
	case KEY_RIGHT:
		moveBlockRight();
		break;
	case KEY_DOWN:
		moveBlockDown();
		updateScore(0, 1);
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
		else PlaySound(rotateSound);
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
	
	int rowsCleared = grid.clearFullRows();
	
	if (rowsCleared) {
		PlaySound(clearSound);
		updateScore(rowsCleared, 0);
	}
}

bool Game::blockFits()
{
	std::vector<Position> tiles = currentBlock.getCellPositions();
	for (Position item : tiles)
		if (grid.isCellEmpty(item.row, item.column) == false)
			return false;
	return true;
}

void Game::Reset()
{
	grid.Initialize();
	blocks = getAllBlocks();
	currentBlock = getRandomBlock();
	nextBlock = getRandomBlock();
	score = 0;
}

void Game::updateScore(int linesCleared, int moveDownPoints)
{
	switch(linesCleared){
		case 1: 
			score += 100;
			break;
		case 2:
			score += 300;
			break;
		case 3:
			score += 500;
			break;
		default: 
			break;
	}

	score += moveDownPoints;
}
