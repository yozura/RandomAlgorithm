#include <stdint.h>
#include <stdio.h>
#include <time.h>

struct xorshift32_state
{
    uint32_t a;
};

uint32_t xorshift32(struct xorshift32_state *state)
{
    uint32_t x = state->a;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    return state->a = x;
}

struct xorshift64_state
{
    uint64_t a;
};

uint64_t xorshift64(struct xorshift64_state *state)
{
    uint64_t x = state->a;
    x ^= x << 13;
    x ^= x >> 7;
    x ^= x << 17;
    return state->a = x;
}

struct xorshift128_state
{
    uint32_t x[4];
};

uint32_t xorshift128(struct xorshift128_state *state)
{
    uint32_t t = state->x[3];
    uint32_t s = state->x[0];
    state->x[3] = state->x[2];
    state->x[2] = state->x[1];
    state->x[1] = s;

    t ^= t << 1;
    t ^= t >> 8;
    return state->x[0] = t ^ s ^ (s >> 19);
}

int main()
{
    struct xorshift64_state state;
    int i;

    state.a = time(NULL);
    for (i = 1; i <= 100; ++i)
    {
        printf("%3lu ", xorshift64(&state) % 100);
        if (i % 10 == 0)
        {
            printf("\n");
        }
    }
    return 0;
}
