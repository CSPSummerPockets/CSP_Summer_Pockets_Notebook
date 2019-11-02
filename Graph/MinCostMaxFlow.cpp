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
#define taskname "WIFI"
//#define BeztDonkey

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

using namespace std;

const int maxN = 200, maxM = 50;
const int maxV = maxN + maxM + 4;
const int maxE = maxN * maxM + maxN + (maxM << 1) + 2;
const int max2E = maxE << 1;
const int Inf = 1e9;

struct TPoint
{
    int x, y;
} a[maxN], b;
struct TEdge
{
    int v, cf, cost;
} e[max2E];
int trace[maxV], d[maxV], m, n, s, t, t1, t2, E = 0, cost = 0;
vector<int> adj[maxV];
queue<int> q;
static bool inQ[maxV];

inline void AddEdge(int u, int v, int c, int cost)
{
    adj[u].push_back(E); e[E++] = {v, c, cost};
    adj[v].push_back(E); e[E++] = {u, 0, -cost};
}

inline int Sqr(int a) { return a * a; }

void Inp()
{
    cin >> m >> n;
    s = n + m; t = s + 1;
    t1 = s + 2; t2 = s + 3;
    int q = n / m;
    for (int i = 0; i < m; ++i)
    {
        cin >> (a + i)->x >> (a + i)->y;
        AddEdge(i + n, t1, q, 0);
        AddEdge(i + n, t2, 1, 0);
    }
    AddEdge(t1, t, q * m, 0);
    AddEdge(t2, t, n - q * m, 0);
    for (int j = 0; j < n; ++j)
    {
        cin >> b.x >> b.y;
        AddEdge(s, j, 1, 0);
        for (int i = 0; i < m; ++i)
            AddEdge(j, i + n, 1, Sqr((a + i)->x - b.x) + Sqr((a + i)->y - b.y));
    }
}

inline bool Minimize(int &a, int b) { return a > b ? a = b, 1 : 0; }

inline bool FindAugmentPath()
{
    memset(trace, -1, sizeof trace);
    fill(begin(d), end(d), Inf);
    d[s] = 0;
    inQ[s] = 1; q.push(s);
    trace[s] = -2;
    while (!q.empty())
    {
        int u = q.front();
        inQ[u] = 0; q.pop();
        int v, du = d[u];
        for (int i : adj[u])
            if (e[i].cf > 0 && Minimize(d[v = e[i].v], du + e[i].cost))
            {
                if (!inQ[v]) inQ[v] = 1, q.push(v);
                trace[v] = i;
            }
    }
    return trace[t] != -1;
}

inline void AugmentFlow()
{
    int flow = Inf, u, i;
    for (u = t; (i = trace[u]) != -2; u = e[i ^ 1].v) flow = min(flow, e[i].cf);
    for (u = t; (i = trace[u]) != -2; u = e[i ^ 1].v)
    {
        e[i].cf -= flow;
        e[i ^ 1].cf += flow;
    }
    cost += d[t];
}

void MinCostMaxFlow()
{
    while (FindAugmentPath()) AugmentFlow();
    cout << cost << '\n';
    for (int j = 0; j < n; ++j)
    {
        int link, v;
        for (int i : adj[j])
            if (e[i].cf == 0 && (v = e[i].v) < n + m) { link = v; break; }
        cout << link - n + 1 << ' ';
    }
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
    MinCostMaxFlow();

    #ifdef BeztDonkey
    auto end = chrono::steady_clock::now();
    cerr << "In milliseconds : "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cerr << '\n' << "In seconds : "
         << chrono::duration_cast<chrono::seconds>(end - start).count() << '\n';
    #endif
    return 0;

}
