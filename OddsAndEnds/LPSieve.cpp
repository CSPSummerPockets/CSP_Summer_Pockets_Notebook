int nP = -1, cnt = 99, i, j, k, t;
static int lp[N], p[N];

inline void Sieve(int i)
{
    int &lpi = lp[i];
    if (lpi == 0)
    {
        p[++nP] = lpi = i;
        if (++cnt == 100) Cout(i, '\n'), cnt = 0;
    }
    for (j = 0; j <= nP; ++j)
        if ((k = p[j]) > lpi || (t = k * i) >= N) break;
        else lp[t] = k;
}

int main()
{
    Sieve(2);
    Sieve(3);
    for (i = 5; i < N; i += 4)
    {
        Sieve(i);
        if ((i += 2) < N) Sieve(i);
    }
}
