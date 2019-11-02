//sqrt(n) * (n + m)
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
#define taskname "MATCH1"
//#define BeztDonkey

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

using namespace std;

const int maxX = 101, maxY = 101;

static int match[maxY], lv[maxY], nX, nY, x, y;
vector<int> S, adj[maxX];
bool found;

inline bool Layering()
{
    queue<int> q;
    memset(lv + 1, 0, nY << 2);
    for (int x : S)
        for (int y : adj[x])
            if (lv[y] == 0) lv[y] = 1, q.push(y);
    while (!q.empty())
    {
        int y = q.front(), x, lvy = lv[y] + 1; q.pop();
        if ((x = match[y]) == 0) return 1;
        for (int y : adj[x])
            if (lv[y] == 0) lv[y] = lvy, q.push(y);
    }
    return 0;
}

inline void AugmentMatching(int x, int lvx)
{
    for (int y : adj[x])
        if (lv[y] == lvx + 1)
        {
            lv[y] = 0;
            if (match[y] == 0) found = 1;
            else AugmentMatching(match[y], lvx + 1);
            if (found)
            {
                match[y] = x;
                return;
            }
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

    scanf("%d%d", &nX, &nY);
    while (scanf("%d%d", &x, &y) != EOF) adj[x].push_back(y);
    S.reserve(nX);
    for (int x = 1; x <= nX; ++x) S.push_back(x);
    while (Layering())
        for (auto it = S.rbegin(); it != S.rend(); ++it)
        {
            found = 0;
            AugmentMatching(*it, 0);
            if (found) *it = S.back(), S.pop_back();
        }
    cout << nX - S.size() << '\n';
    for (int y = 1; y <= nY; ++y)
        if (match[y]) cout << match[y] << ' ' << y << '\n';

    #ifdef BeztDonkey
    auto end = chrono::steady_clock::now();
    cerr << "In milliseconds : "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cerr << '\n' << "In seconds : "
         << chrono::duration_cast<chrono::seconds>(end - start).count() << '\n';
    #endif
    return 0;

}
