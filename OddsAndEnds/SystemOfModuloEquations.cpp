#include<iostream>
#include<ctime>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<climits>
#include<cstring>
#include<iomanip>
#include<string>
#include<bitset>
#include<unordered_map>
#include<unordered_set>
#include<set>
#include<vector>
#include<map>
#include<queue>
#include<stack>
#include<deque>
#include<algorithm>
#include<functional>
#include<chrono>
//#include<windows.h>
//#include<direct.h>
#include<random>
#include<sstream>

#define y0 asdahsdlkahsdad
#define y1 aasdfasdfasdf
#define yn askfhwqriuperikldjk
#define j1 assdgsdgasghsf
#define taskname "COUNTMOD"
//#define BeztDonkey

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

using namespace std;

const int n = 4;
const ll LInf = LLONG_MAX;

struct TEqua
{
    ll a, b;
} f, g;
int T;

inline ll Mul(ll a, ll b, ll Mod)
{
    ll q = (ld)a * b / Mod;
    ll r = (a * b - q * Mod) % Mod;
    if (r < 0) r += Mod;
    return r;
}

inline ll Diophantine(ll m, ll n, ll c)
{
    ll xm = 1, xn = 0;
    while (n)
    {
        ll q = m / n;
        ll r = m - q * n;
        ll xr = xm - q * xn;
        m = n; xm = xn;
        n = r; xn = xr;
    }
    if (c % m) return LInf;
    return xm * (c / m);
}

inline TEqua NewTEqua(const TEqua &f, const TEqua &g)
{
    if (f.b == LInf) return f;
    ll y = Diophantine(f.a, -g.a, g.b - f.b);
    if (y == LInf) return {LInf, LInf};
    ll Mod = f.a * g.a / __gcd(f.a, g.a);
    return {Mod, (Mul(f.a, y, Mod) + f.b) % Mod};
}

inline ll Solve()
{
    cin >> f.a >> f.b;
    for (int i = 1; i < n; ++i) cin >> g.a >> g.b, f = NewTEqua(f, g);
    if (f.b == 0) f.b = f.a;
    return f.b == LInf ? -1 : f.b;
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

    cin >> T;
    while (--T >= 0) cout << Solve() << '\n';

    #ifdef BeztDonkey
    auto end = chrono::steady_clock::now();
    cerr << "In milliseconds : "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cerr << '\n' << "In seconds : "
         << chrono::duration_cast<chrono::seconds>(end - start).count() << '\n';
    #endif
    return 0;

}
