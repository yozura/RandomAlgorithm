#pragma once

class Walker
{
public:
	Walker();
	Walker(const Walker& other);
	~Walker();

	bool Walk(int nextX, int nextY, int width, int height);
	void SetPos(int x, int y);
	void SetStride(int stride);
	void SetId(int id);
	void SetDone(bool done);

	int GetPosX();
	int GetPosY();
	int GetStride();
	int GetWalkCount();
	int GetID();
	bool GetDone();

private:
	static int uid;
	int m_id;
	int m_posX, m_posY;
	int m_stride;
	int m_walkCount;
	bool m_done;
};