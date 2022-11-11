#pragma once

#include <memory.h>
#include <windows.h>
#include <iostream>

class Board
{
public:
	Board(int width, int height);
	Board(const Board&);
	~Board();

	void PaintBoard(int code, int x, int y);
	void DrawBoard();

	void SetWalkerCount(int walkerCount);

	int GetWidth();
	int GetHeight();

private:
	int** m_board;
	int m_width, m_height;
	int m_walkerCount;
};

