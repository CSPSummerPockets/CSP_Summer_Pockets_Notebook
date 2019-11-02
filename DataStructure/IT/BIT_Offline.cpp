#include <bits/stdc++.h>
vector<int> bit[N], lab[N];

inline void Zip(vector<int> &v)
{ sort(v.begin(), v.end()); v.erase(unique(v.begin(), v.end()), v.end()); }
inline void Maximize(int &a, int b) { if (a < b) a = b; }
inline void AddUpdate(int i, int _j)
{ for (; i <= cnta; i += i & -i) lab[i].push_back(_j); }
inline void AddGet(int i, int _j)
{ for (; i > 0; i &= i - 1) lab[i].push_back(_j); }
#define Mapping (upper_bound(lab[i].begin(), lab[i].end(), _j) - lab[i].begin())
inline void Update(int i, int _j, int val)
{
    for (; i <= cnta; i += i & -i)
        for (int j = Mapping, lim = lab[i].size(); j <= lim; j += j & -j)
            Maximize(bit[i][j], val);
}
inline int Get(int i, int _j)
{
    int res = 0;
    for (; i > 0; i &= i - 1)
        for (int j = Mapping; j > 0; j &= j - 1) res = max(res, bit[i][j]);
    return res;
}
void Solve()
{
    for (int i = 1; i <= n; ++i) AddUpdate(x[i].a, x[i].b), AddGet(x[i].a - 1, x[i].b - 1);
    for (int i = 1; i <= cnta; ++i) Zip(lab[i]), bit[i].resize(lab[i].size() + 1, 0);
    for (int i = 1; i <= n; ++i)
    {
        int f = Get(x[i].a - 1, x[i].b - 1) + 1;
        ans = max(ans, f);
        Update(x[i].a, x[i].b, f);
    }
    cout << ans;
}
//LIS2_SPOJ
