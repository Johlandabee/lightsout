#pragma once

#include "Helper.h"

#include <stdio.h>
#include <Windows.h>
#include <sstream>

#include "Colors.h"

namespace lightsout {
	class Light {
	public:
		Light(const short& bufferPosX, const short& bufferPosY,
			const short& fontWidth, const short& fontHeight, const bool& isOn = false) {
			this->bufferPos_ = {
				bufferPosX,
				bufferPosY
			};

			this->rect_ = {
				bufferPosX * fontWidth,
				bufferPosY * fontHeight,
				(bufferPosX + 1) * fontWidth,
				(bufferPosY + 1) * fontHeight
			};

			this->isOn_ = isOn;
		}

		char Char() {
			return this->isOn_ ? '1' : '0';
		}

		void Switch() {
			this->isOn_ = this->isOn_ ? false : true;
		}

		bool IsOn() {
			return this->isOn_;
		}

		void Update(const HWND& hwnd, bool* changed) {
			POINT p;

			GetCursorPos(&p);
			ScreenToClient(hwnd, &p);

			RECT r = {
				this->rect_.Left,
				this->rect_.Top,
				this->rect_.Right,
				this->rect_.Bottom
			};

			bool hoover = (PtInRect(&r, p) != 0);
			bool leftClick = lightsout::Helper::IsLeftMouseButtonDown();

			bool x = hoover && leftClick;

			if (x)
				this->Switch();


			*changed = x;
		}

		void Draw(const HANDLE& stdh) {
			CHAR_INFO ci[1];
			ci[0].Char.AsciiChar = Char();
			ci[0].Attributes = isOn_ ? FG_Yellow : FG_Gray;

			COORD cbs = { 1, 1 };
			COORD pos = { 0 ,0 };

			SMALL_RECT rect = {
				this->bufferPos_.X,
				this->bufferPos_.Y,
				this->bufferPos_.X,
				this->bufferPos_.Y
			};

			WriteConsoleOutput(stdh, ci, cbs, pos, &rect);
		}

		SMALL_RECT GetRect() {
			return rect_;
		}

	private:
		bool isOn_ = false;

		COORD bufferPos_;
		SMALL_RECT rect_;
	};
}