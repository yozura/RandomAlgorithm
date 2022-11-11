#include "CWalker.h"

int Walker::uid = 0;

Walker::Walker()
	: m_id(++uid)
	, m_posX(0), m_posY(0)
	, m_stride(0)
	, m_walkCount(0)
	, m_done(0)
{}

Walker::Walker(const Walker& other)
{
	m_id = other.m_id;
	m_posX = other.m_posX;
	m_posY = other.m_posY;
	m_stride = other.m_stride;
	m_walkCount = other.m_walkCount;
	m_done = other.m_done;
}

Walker::~Walker() {}

bool Walker::Walk(int dirX, int dirY, int width, int height)
{
	// 만약 벽에 부딪히면 종료~
	int nextX = m_posX + dirX;
	int nextY = m_posY + dirY;
	if (nextX < 0 || nextX >= width || nextY < 0 || nextY >= height)
		return false;

	m_posX = nextX;
	m_posY = nextY;
	++m_walkCount;
	return true;
}

void Walker::SetPos(int x, int y)
{
	m_posX = x;
	m_posY = y;
}

void Walker::SetDone(bool done)
{
	m_done = done;
}

void Walker::SetStride(int stride)
{
	m_stride = stride;
}

int Walker::GetPosX()
{
	return m_posX;
}

int Walker::GetPosY()
{
	return m_posY;
}

int Walker::GetStride()
{
	return m_stride;
}

int Walker::GetWalkCount()
{
	return m_walkCount;
}

int Walker::GetID()
{
	return m_id;
}

bool Walker::GetDone()
{
	return m_done;
}

