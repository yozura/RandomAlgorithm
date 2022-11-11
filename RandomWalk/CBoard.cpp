#include "CBoard.h"

Board::Board(int width, int height)
	: m_width(width)
	, m_height(height)
	, m_walkerCount(0)
{
	m_board = new int*[height];
	for (int i = 0; i < height; ++i)
		m_board[i] = new int[width];

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			m_board[y][x] = 0;
		}
	}
}

Board::Board(const Board& other) 
{
	m_width = other.m_width;
	m_height = other.m_height;
	m_walkerCount = other.m_walkerCount;
	memcpy(m_board, other.m_board, sizeof(m_board));
}

Board::~Board() 
{
	if (m_board)
	{
		for (int i = 0; i < m_height; ++i)
			delete[] m_board[i];
		delete[] m_board;
	}
}

void Board::PaintBoard(int code, int x, int y)
{
	m_board[y][x] = code;
}

void Board::DrawBoard()
{
	for (int y = 0; y < m_height; ++y)
	{
		for (int x = 0; x < m_width; ++x)
		{
			switch (m_board[y][x])
			{
			case 1: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1); break;
			case 2: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2); break;
			case 3:	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3); break;
			case 4: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4); break;
			case 5: SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5); break;
			}

			std::cout << "■";
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		}
		std::cout << '\n';
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

void Board::SetWalkerCount(int walkerCount)
{
	m_walkerCount = walkerCount;
}

int Board::GetWidth()
{
	return m_width;
}

int Board::GetHeight()
{
	return m_height;
}
