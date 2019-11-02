#include <bits/stdc++.h>
#define taskname "READERS"

//#define BeztDonkey
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

using namespace std;

const int maxN = 1e5 + 9;

struct TVector
{
    ll x, y;
    inline TVector operator - (const TVector &other) const &
    { return {x - other.x, y - other.y}; }
    inline ll operator * (const TVector &other) const &
    { return x * other.y - other.x * y; }
} a[maxN];
inline bool CCW(const TVector& a, const TVector& b, const TVector& c)
{
    #define XInterSect(a, b) (double(a.y - b.y) / (b.x - a.x))
    return XInterSect(a, b) > XInterSect(b, c);
    return (b - a) * (c - a) > 0;
}

static ll s, start;
int n, m, PrevC, C;

void Prepare()
{
    cin >> n >> m;
    int p = 0;
    for (int i = 1; i <= n; ++i)
    {
        cin >> C;
        TVector tmp = {s + C, s};
        s += C;
        while (p >= 2 && !CCW(a[p - 1], a[p], tmp)) --p;
        a[++p] = tmp;
    }
    n = p;
}

inline ll Time(const TVector& t)
{
    int low = 2, high = n, mid;
    while (low <= high)
    {
        mid = low + high >> 1;
        if ((a[mid] - a[mid - 1]) * t >= 0) low = mid + 1;
        else high = mid - 1;
    }
    return a[high] * t;
}

void Solve()
{
    cin >> PrevC;
    for (int i = 2; i <= m; ++i)
    {
        cin >> C;
        start += Time({C, PrevC});
        PrevC = C;
    }
    cout << start + s * PrevC;
}

int main()
{
    #ifdef BeztDonkey
    auto start = chrono::steady_clock::now();
    #endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen(taskname".inp", "r", stdin);
    freopen(taskname".out", "w", stdout);

    Prepare();
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
