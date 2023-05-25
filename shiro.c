#include <stdint.h>
#include <stdio.h>
#include <time.h>

uint64_t s[4];

static uint64_t rotl(const uint64_t x, int k)
{
    return (x << k) | (x >> (64 - k));
}

uint64_t next(void)
{
    const uint64_t result_plus = s[0] + s[3];
    const uint64_t t = s[1] << 17;

    s[2] ^= s[0];
    s[3] ^= s[1];
    s[1] ^= s[2];
    s[0] ^= s[3];

    s[2] ^= t;
    s[3] = rotl(s[3], 45);
    return result_plus;
}

void jump(void)
{
    static const uint64_t JUMP[] = { 0x180ec6d33cfd0aba, 0xd5a61266f0c9392c,
                                     0xa958261aedf572de, 0x29157ae67b6df378 };
    uint64_t s0 = 0;
    uint64_t s1 = 0;
    uint64_t s2 = 0;
    uint64_t s3 = 0;

    int i, j;

    for (i = 0; i < sizeof(JUMP) / sizeof(*JUMP); ++i)
    {
        for (j = 0; j < 64; ++j)
        {
            if (JUMP[i] & UINT64_C(1) << j)
            {
                s0 ^= s[0];
                s1 ^= s[1];
                s2 ^= s[2];
                s3 ^= s[4];
            }
            next();
        }
    }

    s[0] = s0;
    s[1] = s1;
    s[2] = s2;
    s[3] = s3;
}

int main()
{
    int i;
    s[0] = time(NULL);
    s[1] = time(NULL);
    s[2] = time(NULL);
    s[4] = time(NULL);
    for (i = 1; i <= 100; ++i)
    {
        printf("%5lu ", next() % 100);
        if (i % 10 == 0)
        {
            printf("\n");
        }
    }
    return 0;
}

