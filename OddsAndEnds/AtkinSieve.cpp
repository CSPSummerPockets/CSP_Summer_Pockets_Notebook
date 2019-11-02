static int sieve[(N + 1 >> 1) + 31 >> 5];
int x, y, a, t, r, sqrtN = sqrt(N);

#define Flip(t) sieve[t >> 6] ^= 1 << (t >> 1 & 31)
#define Read(t) (sieve[t >> 6] & 1 << (t >> 1 & 31))
inline void Sieve(int t)
{
    if (Read(t) == 0) return;
    for (a = (t *= t), t <<= 1; a <= N; a += t) sieve[a >> 6] &= ~(1 << (a >> 1 & 31));
}

int main()
{
    for (x = sqrt(double(N - 1) / 4); x > 0; --x)
        for (a = x * x << 2, y = sqrt(N - a); y > 0; --y)
            if ((r = (t = a + y * y) % 12) == 1 || r == 5) Flip(t);
    for (x = sqrt(double(N - 1) / 3); x > 0; --x)
        for (a = x * x * 3, y = sqrt(N - a); y > 0; --y)
            if ((t = a + y * y) % 12 == 7) Flip(t);
    for (x = sqrt(double(N - 1) / 2); x > 0; --x)
        for (a = x * x * 3, y = max((int)ceil(sqrt(a - N)), 0); y < x; ++y)
            if ((t = a - y * y) % 12 == 11) Flip(t);
    for (t = 5; t <= sqrtN; t += 6) Sieve(t), Sieve(t + 2);

    return 0;
}
