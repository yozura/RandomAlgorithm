#include <stdio.h>
#include <math.h>

int _mid_sqr(int seed, int digit);

int main(int argc, char* argv[])
{
    printf("%d\n", _mid_sqr(2557, 4));
    return 0;
}

int _mid_sqr(int seed, int digit)
{
    int sqr, sqrDigit, i, answer;

    sqr = seed * seed;
    sqrDigit = (int)log10((double)sqr) + 1;

    for (i = 0; i < (sqrDigit - digit) / 2; ++i)
    {
        sqr /= 10;
    }
    
    answer = sqr % (int)pow(10, digit);
    return answer;
}
