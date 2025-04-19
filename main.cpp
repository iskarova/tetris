#include <iostream>
#include "raylib.h"
#include "grid.h"

using namespace std;
int main() {

	Color darkBlue = { 44, 44, 127, 255 };
	InitWindow(300, 600, "tetris");
	SetTargetFPS(60);

	Grid grid = Grid();
	grid.Print();

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(darkBlue);
		grid.Draw();

		EndDrawing();
	}

	CloseWindow();
	return 0;
}