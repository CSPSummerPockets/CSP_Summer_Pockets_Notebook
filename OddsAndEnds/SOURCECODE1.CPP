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
#include<random>
#include<sstream>

#define y0 asdahsdlkahsdad
#define y1 aasdfasdfasdf
#define yn askfhwqriuperikldjk
#define j1 assdgsdgasghsf
#define taskname "TEST"

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

using namespace std;

template<typename T> inline void Cin(T &x)
{
    register char c;
    bool neg = 0;
    for (c = getchar(); c < '0' || c > '9'; c = getchar())
        if (c == '-') neg = 1;
    for (x = 0; c >= '0' && c <= '9'; c = getchar())
        x = x * 10 + c - '0';
    if (neg) x = -x;
}
template<typename T, typename... Ts> inline void Cin(T& x, Ts&... xs) { Cin(x); Cin(xs...); }
template<typename T> inline void Out(const T x) { if (x > 9) Out(x / 10); putchar(x % 10 + '0'); }
template<typename T> inline void Cout(const T x) { if (x < 0) putchar('-'), Out(-x); else Out(x); }
template<typename T> inline void Cout(const T x, const char c) { Cout(x); putchar(c); }
template<typename T, typename... Ts> inline void Cout(const T x, const char c, const Ts... xs) { Cout(x); putchar(c); Cout(xs...); }

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen(taskname".inp", "r", stdin);
    freopen(taskname".out", "w", stdout);



    return 0;
}
