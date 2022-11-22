/* 
    출처 : https://kldp.org/node/135244
    
    rand 함수의 원리를 눈으로 파악하기에 좋은 교보재인듯합니다.
*/

#include <stdio.h>
#include <time.h>

unsigned int _next = 0;
void _srand(unsigned int seed);
int _rand(void);

void SetSeedAndPrint(int i);

int main(void)
{
    int i;

    for (i = 0; i < 10000000; ++i)
        SetSeedAndPrint(i);

    return 0;
}

void _srand(unsigned int seed)
{
    _next = seed;
}

int _rand(void)
{
    _next = 1103515245 * _next + 12345;
    return (_next / 65536) % 32768;
}

void SetSeedAndPrint(int i)
{
    int result = (int)time(0);
    _srand(result);
    printf("i:%10d, Time: %d, rand(): %d\n", i, result, _rand());
}