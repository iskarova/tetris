#include <iostream>
#include "raylib.h"
#include "game.h"

double lastUpdateTime = 0;
bool eventTriggered(double interval);

using namespace std;
int main() {

	Color darkBlue = { 44, 44, 127, 255 };
	InitWindow(300, 600, "tetris");
	SetTargetFPS(60);

	Game game = Game();

	while (!WindowShouldClose()) {
		game.handleInput();
		if (eventTriggered(0.05)) {
			game.moveBlockDown();
		}
		BeginDrawing();
		ClearBackground(darkBlue);
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