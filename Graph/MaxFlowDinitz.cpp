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

const int maxN = 1001, maxM = 1e4, maxC = 1e9, max2M = maxM << 1;
const ll LInf = (ll)maxC * maxM;

struct TEdge
{
    int u, v, cf;
} e[max2M];
stack<int> ans;
int h[maxN], head[maxN], current[maxN], link[max2M], n, m, s, t, u, v, c;

void Inp()
{
    Cin(n); Cin(m);
    s = 1; t = n;
    memset(head + 1, -1, n << 2);
    for (int i = 0; i < m; ++i)
    {
        Cin(u); Cin(v); Cin(c);
        link[i << 1] = head[u]; head[u] = i << 1;
        e[i << 1] = {u, v, c};
        e[i << 1 | 1] = {v, u, c};
        link[i << 1 | 1] = head[v]; head[v] = i << 1 | 1;
    }
}

inline void BFS()
{
    queue<int> q;
    memset(h + 1, -1, n << 2);
    h[t] = 0;
    q.push(t);
    while (!q.empty())
    {
        int u = q.front(), v, hv = h[u] + 1; q.pop();
        for (int i = head[u]; i != -1; i = link[i])
        {
            if (e[i ^ 1].cf == 0 || h[v = e[i ^ 1].u] != -1) continue;
            h[v] = hv;
            if (v == s) return;
            q.push(v);
        }
    }
}

inline int DFS(int u, ll flowIn)
{
    if (u == t) return flowIn;
    int flowOut = 0, v, hv = h[u] - 1;
    for (auto &i = current[u]; i != -1; i = link[i])
    {
        if (h[v = e[i].v] != hv || e[i].cf == 0) continue;
        int q = DFS(v, min((ll)e[i].cf, flowIn));
        e[i].cf -= q;
        e[i ^ 1].cf += q;
        flowIn -= q;
        flowOut += q;
        if (flowIn == 0) break;
    }
    return flowOut;
}

inline void BFS1()
{
    queue<int> q;
    memset(h + 1, -1, n << 2);
    h[s] = 0;
    q.push(s);
    while (!q.empty())
    {
        int u = q.front(), v; q.pop();
        for (int i = head[u]; i != -1; i = link[i])
        {
            if (e[i].cf == 0 || h[v = e[i].v] != -1) continue;
            h[v] = 0;
            if (v == t) return;
            q.push(v);
        }
    }
}

void Solve()
{
    int dem = 0;
    while (BFS(), h[s] != -1)
    {
        copy(head + 1, head + n + 1, current + 1);
        dem += DFS(s, LInf);
    }
    ll cutVal = 0;
    BFS1();
    for (int u = 1; u <= n; ++u)
    {
        if (h[u] == -1) continue;
        for (int i = head[u]; i != -1; i = link[i])
            if (h[e[i].v] == -1) cutVal += e[i ^ 1].cf, ans.push(i);
    }
    cout << (cutVal >> 1) << '\n';
    while (!ans.empty()) cout << (ans.top() >> 1) + 1 << ' ', ans.pop();
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
