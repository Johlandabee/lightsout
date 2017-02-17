#pragma once

#include <iostream>
#include <stdio.h>
#include <vector>
#include <Windows.h>

#include <time.h>

#include "Light.h"
#include "Helper.h"

int main(int argc, char** argv) {
	SetConsoleTitle("lightsout.exe - 0.0.1");

	HWND hwnd = GetConsoleWindow();
	HANDLE stdh = GetStdHandle(STD_OUTPUT_HANDLE);

	if (stdh == INVALID_HANDLE_VALUE || hwnd == INVALID_HANDLE_VALUE) {
		std::cout << "Invalid handle!" << std::endl;
		return 1;
	}

	lightsout::Helper::HideCursor(stdh);

	const int size = 10;

	std::vector<std::vector<lightsout::Light>> board(size);

	// ToDo: Center...
	int x = 50, y = 10;

	COORD fontSize = lightsout::Helper::GetFontSize(stdh);

	srand(static_cast<int>(time(NULL)));
	for (auto i = 0; i < size; i++) {
		for (auto j = 0; j < size; j++) {
			board[i].push_back(
				lightsout::Light(x + i, y + j, fontSize.X, fontSize.Y, (rand() % 2) > 0)
			);
		}
	}

	const int radius = 1;

	bool right = true;
	bool left = true;

	bool lightsOn = true;

	while (lightsOn) {
		lightsOn = false;

		for (int xa = 0; xa < size; xa++) {
			for (int ya = 0; ya < size; ya++) {
				if (board[xa][ya].IsOn()) {
					lightsOn = true;
				}

				bool changed = false;

				board[xa][ya].Update(hwnd, &changed);
				board[xa][ya].Draw(stdh);

				if (changed) {
					if (left) {
						for (auto xb = xa - 1; xb > 0 && xb >= xa - radius; --xb) {
							for (auto yb = ya; yb > 0 && yb >= ya - radius; --yb) {
								board[xb][yb].Switch();
							}
						}

						//ToDo: Top right, bottom left
					}

					if (right) {
						for (auto xc = xa + 1; xc < size && xc <= xa + radius; ++xc) {
							for (auto yc = ya; yc < size && yc <= ya + radius; ++yc) {
								board[xc][yc].Switch();
							}
						}

						//ToDo: Top right, bottom left
					}
				}
			}
		}

		Sleep(133);
	}

	std::cout << "You made it!" << std::endl;

	std::cin.ignore();
}