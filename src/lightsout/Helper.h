#pragma once

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <Windows.h>

namespace lightsout {
	class Helper {
	public:
		static COORD GetBufferSize(const HWND& stdh) {
			CONSOLE_SCREEN_BUFFER_INFOEX info;

			info.cbSize = sizeof(CONSOLE_SCREEN_BUFFER_INFOEX);

			GetConsoleScreenBufferInfoEx(stdh, &info);

			return info.dwSize;
		}

		static COORD GetFontSize(const HANDLE& stdh) {
			CONSOLE_FONT_INFOEX info;

			info.cbSize = sizeof(CONSOLE_FONT_INFOEX);

			GetCurrentConsoleFontEx(stdh, false, &info);

			return info.dwFontSize;
		}

		static bool IsLeftMouseButtonDown() {
			return ((GetKeyState(VK_LBUTTON) & 0x100) != 0);
		}

		static void HideCursor(const HANDLE& stdh) {
			CONSOLE_CURSOR_INFO cursorInfo;

			GetConsoleCursorInfo(stdh, &cursorInfo);

			cursorInfo.bVisible = false;

			SetConsoleCursorInfo(stdh, &cursorInfo);
		}
	};
}