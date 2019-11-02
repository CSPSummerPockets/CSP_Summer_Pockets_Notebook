#include <bits/stdc++.h>
#define taskname "PRINTERS"

//#define BeztDonkey
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

using namespace std;

const int maxN = 1e5 + 9;

#define x first
#define y second
pair<int, int> a[maxN];
typedef pair<int, ll> TLine;
TLine b[maxN];
int n, m, j;

void Inp()
{
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i].x >> a[i].y;
}

inline TLine operator - (const TLine& a, const TLine& b)
{
    return {a.x - b.x, a.y - b.y};
}
inline ll operator * (const TLine& a, const TLine& b)
{
    return a.x * b.y - a.y * b.x;
}
#define XInterSect(a, b) (double(a.y - b.y) / (b.x - a.x))
inline bool Erase(const TLine& a, const TLine& b, const TLine& c)
{
    //return XInterSect(a, c) >= XInterSect(b, c);
    //return (a.y - c.y) * (b.x - c.x) <= (c.x - a.x) * (c.y - b.y);
    return (b - a) * (c - a) > 0;
}

inline void AddLine(const TLine &t)
{
    while (n >= 2 && Erase(b[n - 1], b[n], t)) --n;
    b[++n] = t;
}

#define GetVal(j, t) (b[j].x * (t) + b[j].y)
inline ll Query(ll t)
{
    if (j > n) j = n;
    else while (j < n && GetVal(j, t) >= GetVal(j + 1, t)) ++j;
    return GetVal(j, t);
}

void Solve()
{
    sort(a + 1, a + n + 1);
    m = 0;
    for (int i = 1; i <= n; ++i)
    {
        while (m > 0 && a[m].y <= a[i].y) --m;
        a[++m] = a[i];
    }
    //f[i] = min(a[i].x * a[j + 1].y + f[j]) voi j tu 0 den i - 1
    ll f = n = 0; j = 1;
    for (int i = 1; i <= m; ++i)
    {
        AddLine({a[i].y, f});
        f = Query(a[i].x);
    }
    cout << f;
}

int main()
{
    #ifdef BeztDonkey
    auto start = chrono::steady_clock::now();
    #endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    //freopen(taskname".inp", "r", stdin);
    //freopen(taskname".out", "w", stdout);

    Inp();
    Solve();

    #ifdef BeztDonkey
    auto end = chrono::steady_clock::now();
    cerr << "In milliseconds : "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cerr << '\n' << "In seconds : "
         << chrono::duration_cast<chrono::seconds>(end - start).count() << '\n';
    #endif
    return 0;
}
