#include <bits/stdc++.h>
template<typename T>
struct TBIT
{
    T lab[maxN];
    int n, p;
    inline void Init(int N)
    {
        n = N;
        //fill(lab + 1, lab + 1 + n, 0);
        copy(a + 1, a + 1 + n, lab + 1);
        for (int x = 1; x <= n; ++x)
            for (int y = x - 1, q = x & y; y > q; y &= y - 1) lab[x] += lab[y];
        p = 1;
        while ((p << 1) <= n) p <<= 1;
    }
    inline void Update(int i, T val)
    {
        for (; i <= n; i += i & -i) lab[i] += val;
    }
    inline T Get(int i)
    {
        T ans = 0;
        for (; i > 0; i &= i - 1) ans += lab[i];
        return ans;
    }
    inline int Find(T t)
    {
        int x = 0;
        for (int p1 = p; p1 > 0; p1 >>= 1)
        {
            int y = x + p1;
            if (y <= n && lab[y] <= t) x = y, t -= lab[y];
        }
        return x;
    }
};

template<typename T>
struct TSuperBIT
{
    TBIT<T> a, b;
    inline void Init(int n)
    {
        a.Init(n); b.Init(n);
    }
    inline void Update(int l, int r, T val)
    {
        a.Update(l, val); a.Update(r + 1, -val);
        b.Update(l, val * (l - 1)); b.Update(r + 1, -val * r);
    }
    inline T _Get(int i)
    {
        return a.Get(i) * i - b.Get(i);
    }
    inline T Get(int l, int r)
    {
        return _Get(r) - _Get(l - 1);
    }
}
