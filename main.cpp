#include <iostream>
#include <vector>
#include <thread>
#include <stdio.h>
#include <Windows.h>
using namespace std;

int nScreenWidth = 120;			// Console Screen Size X (columns)
int nScreenHeight = 60;

wstring tetromino[7];
int fieldWidth = 18;
int fieldHeight = 20;
unsigned char* pField = nullptr;

int rotate(int i, int j, int r) {
	switch (r % 4) {
	case 0: return j * 4 + i;	break;			// 0 deg
	case 1: return 12 + j - (i * 4); break;	// 90 deg
	case 2: return 15 - (j * 4) - i; break;	// 180 deg
	case 3: return 3 - j + (i * 4); break;	// 270 deg
	}
}

bool fitting(int tetron, int deg, int x, int y) {
	
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			int piece_index = rotate(i, j, deg);

			int field_index = (y + j) * fieldWidth + (x + i);

			if (x + i >= 0 && x + i < fieldWidth) {
				if (y + j >= 0 && y + j < fieldHeight) {
					if (tetromino[tetron][piece_index] == L'X' && pField[field_index] != 0)
						return false;
				}
			}
		}

	}
	
	return true;
}

int main() {

	tetromino[0].append(L"..X...X...X...X."); // Tetronimos 4x4
	tetromino[1].append(L"..X..XX...X.....");
	tetromino[2].append(L".....XX..XX.....");
	tetromino[3].append(L"..X..XX..X......");
	tetromino[4].append(L".X...XX...X.....");
	tetromino[5].append(L".X...X...XX.....");
	tetromino[6].append(L"..X...X..XX.....");

	pField = new unsigned char[fieldWidth * fieldHeight];
	for (size_t i = 0; i < fieldWidth; i++)
		for (size_t j = 0; j < fieldHeight; j++)
			pField[j * fieldWidth + i] = (i == 0 || i == fieldWidth - 1 || j == fieldHeight - 1) ? 9 : 0;

	// Create Screen Buffer
	wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
	for (size_t i = 0; i < nScreenWidth * nScreenHeight; i++)
		screen[i] = L' ';
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;


	// input

	bool gameOver = false;

	int current_piece = 3;
	int current_deg = 0;
	int current_x = fieldWidth / 2;
	int current_y = 0;

	bool keys[4];
	bool rotateHold = false;
	// output

	while (!gameOver) {

		// timing
		this_thread::sleep_for((std::chrono::milliseconds(110)));

		for (int k = 0; k < 4; k++)								// R   L   D Z
			keys[k] = (0x8000 & GetAsyncKeyState((unsigned char)("\x27\x25\x28Z"[k]))) != 0;

		// logic
		if (keys[0]) { // R
			if (fitting(current_piece, current_deg, current_x + 1, current_y))
				current_x += 1;
		}
		
		if (keys[1]) { // L
			if (fitting(current_piece, current_deg, current_x - 1, current_y)) 
				current_x -= 1;
		}

		if (keys[2]) { // D
			if (fitting(current_piece, current_deg, current_x, current_y + 1))
				current_y += 1;
		}

		if (keys[3]) { // D
			if (!rotateHold && fitting(current_piece, current_deg + 1, current_x, current_y + 1))
				current_deg += 1;
			rotateHold = true;
		}
		else rotateHold = false;

		// draw field
		for (int i = 0; i < fieldWidth; i++)
		{
			for (int j = 0; j < fieldHeight; j++)
			{
				screen[(j+2) * nScreenWidth + (i+6)] = L" ABCDEFG=#"[pField[j * fieldWidth + i]];
			}
		}

		// draw current block
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				if (tetromino[current_piece][rotate(i, j, current_deg)] == L'X')
					screen[(current_y + j + 2) * nScreenWidth + (current_x + i + 6)] = current_piece + 'A';

		// Display Frame
		WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
	}

	system("pause>0");
	return 0;
}