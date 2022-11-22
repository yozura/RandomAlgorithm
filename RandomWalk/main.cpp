#include <iostream>
#include <random>
#include <ctime>
#include <functional>
#include <fstream>

#include "CBoard.h"
#include "CWalker.h"

enum
{
    LEFT = 0,
    UP,
    RIGHT,
    DOWN,
    LEFT_UP,
    LEFT_DOWN,
    RIGHT_UP,
    RIGHT_DOWN,
    DIR = 7
};

void GetNextDir(int rand, int& dirX, int& dirY)
{
    switch (rand)
    {
    case (int)LEFT:         dirX = -1; dirY = 0;     break;
    case (int)UP:           dirX = 0;  dirY = -1;    break;
    case (int)RIGHT:        dirX = 1;  dirY = 0;     break;
    case (int)DOWN:         dirX = 0;  dirY = 1;     break;
    case (int)LEFT_UP:      dirX = -1; dirY = -1;    break;
    case (int)LEFT_DOWN:    dirX = -1; dirY = 1;     break;
    case (int)RIGHT_UP:     dirX = 1;  dirY = -1;    break;
    case (int)RIGHT_DOWN:   dirX = 1;  dirY = 1;     break;
    }
}

static const int WALKER_COUNT = 5;

int main()
{
    // 1. 난수 엔진 생성
    std::mt19937 engine((unsigned int)time(NULL));
    
    // 2. 균등 분포기 생성 
    std::uniform_int_distribution<int> dist(0, (int)DIR);

    // 3. 난수 생성기 생성
    auto generator = bind(dist, engine);

    Board board(50, 50);
    board.SetWalkerCount(WALKER_COUNT);
    board.DrawBoard();

    Walker* walkers = new Walker[WALKER_COUNT];
    for (int i = 0; i < WALKER_COUNT; ++i)
    {
        walkers[i].SetPos(board.GetWidth() / 2, board.GetHeight() / 2);
        board.PaintBoard(walkers[i].GetID(), walkers[i].GetPosX(), walkers[i].GetPosY());
    }

    bool result = false;
    int dirX = 0, dirY = 0, rand;
    ULONGLONG begin, cur, delay;
    begin = GetTickCount64();
    delay = 1000;
    while (!result)
    {
        cur = GetTickCount64();
        if (cur - begin < delay)
            continue;
        begin = cur;

        system("cls");
        for (int i = 0; i < WALKER_COUNT; ++i)
        {
            if (walkers[i].GetDone())
                continue;

            rand = generator();
            GetNextDir(rand, dirX, dirY);

            result = walkers[i].Walk(dirX, dirY, board.GetWidth(), board.GetWidth());
            if (!result) walkers[i].SetDone(!result);

            board.PaintBoard(walkers[i].GetID(), walkers[i].GetPosX(), walkers[i].GetPosY());
        }
        
        // if result is true -> escpae loop
        for (int i = 0; i < WALKER_COUNT; ++i)
        {
            result = walkers[i].GetDone();
            if (!result) break;
        }

        board.DrawBoard();
    }

    std::ofstream fout;
    fout.open("walker_info.txt");
    if (fout.fail())
    {
        std::cout << "Could not open file" << '\n';
        return -1;
    }

    for (int i = 0; i < WALKER_COUNT; ++i)
    {
        fout << "Walker ID : " << walkers[i].GetID() << '\n';
        fout << "Walker WalkCount : " << walkers[i].GetWalkCount() << '\n';
        fout << "Walker LastPos : " << walkers[i].GetPosX() << ", " << walkers[i].GetPosY() << "\n\n";
    }

    std::cout << "Updated 'walker_info.txt' file" << "\n\n";
    fout.close();

    delete[] walkers;
	return 0;
}