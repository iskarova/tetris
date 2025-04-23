#include <iostream>
#include "raylib.h"
#include "game.h"
#include "colors.h"

double lastUpdateTime = 0;
bool eventTriggered(double interval);

using namespace std;
int main() {

	InitWindow(540, 620, "tetris");
	SetTargetFPS(60);

	Font font = LoadFontEx("font/monogram.ttf", 64, 0, 0);

	Game game = Game();

	while (!WindowShouldClose()) {
		game.handleInput();
		if (eventTriggered(0.5)) {
			game.moveBlockDown();
		}
		BeginDrawing();
		ClearBackground(darkBlue);
		DrawTextEx(font, "SCORE", { 375, 15 }, 38, 1.5, WHITE);
		DrawTextEx(font, "NEXT", { 385, 175 }, 38, 1.5, WHITE);
		
		if (game.gameOver)
			DrawTextEx(font, "GAME OVER!", { 335, 450 }, 38, 1.5, MAGENTA);
		
		DrawRectangleRounded({ 340, 55, 170, 60 }, 0.3, 6, lightBlue);
		DrawRectangleRounded({ 340, 215, 170, 180 }, 0.3, 6, lightBlue);
		game.Draw();
		EndDrawing();
	}

	CloseWindow();
	return 0;
}

bool eventTriggered(double interval) {

	double currentTime = GetTime();
	if (currentTime - lastUpdateTime >= interval) {
		lastUpdateTime = currentTime;
		return true;
	}

	return false;
}