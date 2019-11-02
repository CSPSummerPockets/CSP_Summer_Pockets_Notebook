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
#define taskname "DEA"
//#define BeztDonkey

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

using namespace std;

template <typename T> inline void Cin(T &x)
{
    register char c;
    for (c = getchar(); c < '0' || c > '9'; c = getchar());
    for (x = 0; c >= '0' && c <= '9'; c = getchar())
        x = x * 10 + c - '0';
}

const int maxN = 1001, maxM = 1e4, maxC = 1e9;

struct TEdge
{
    int u, v, cf;
} e[maxM << 1];
vector<int> adj[maxN], ans;
int trace[maxN], n, m, s, t, u, v, c;

void Inp()
{
    Cin(n); Cin(m);
    s = 1; t = n;
    for (int i = 0; i < m; ++i)
    {
        Cin(u); Cin(v); Cin(c);
        adj[u].push_back(i << 1);
        e[i << 1] = {u, v, c};
        e[i << 1 | 1] = {v, u, c};
        adj[v].push_back(i << 1 | 1);
    }
}

inline bool FindAugmentPath()
{
    queue<int> q;
    memset(trace + 1, -1, n << 2);
    trace[s] = -2;
    q.push(s);
    while (!q.empty())
    {
        int u = q.front(), v; q.pop();
        for (int i : adj[u])
        {
            if (e[i].cf == 0 || trace[v = e[i].v] != -1) continue;
            trace[v] = i;
            if (v == t) return 1;
            q.push(v);
        }
    }
    return 0;
}

inline void AugmentFlow()
{
    int u, i, del = maxC;
    for (u = t; (i = trace[u]) != -2; u = e[i].u) del = min(del, e[i].cf);
    for (u = t; (i = trace[u]) != -2; u = e[i].u) e[i].cf -= del, e[i ^ 1].cf += del;
}

void Solve()
{
    while (FindAugmentPath()) AugmentFlow();
    ll cutVal = 0;
    for (int u = 1; u <= n; ++u)
    {
        if (trace[u] == -1) continue;
        for (int i : adj[u])
            if (trace[e[i].v] == -1) cutVal += e[i ^ 1].cf, ans.push_back(i);
    }
    cout << (cutVal >> 1) << '\n';
    for (int i : ans) cout << (i >> 1) + 1 << ' ';
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
