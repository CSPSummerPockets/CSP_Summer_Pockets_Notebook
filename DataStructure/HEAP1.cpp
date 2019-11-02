#include <bits/stdc++.h>
#define taskname "TEST"

//#define Bang
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

using namespace std;

typedef pair<int, int> TPair;

template<typename TComparer>
class THeap
{
public:
    priority_queue<TPair, vector<TPair>, TComparer> pq;
    bool inS[maxN];
    inline void Init()
    {
        fill_n(inS, maxN, 0);
        while (!pq.empty()) pq.pop();
    }
    inline void Push(int x)
    {
        if (inS[x]) return;
        inS[x] = 1;
        pq.emplace(x, a[x]);
    }
    inline void Pop(int x)
    {
        inS[x] = 0;
    }
    inline void Change(int x, int k)
    {
        a[x] = k;
        pq.emplace(x, k);
    }
    inline bool Invalid(const TPair &p)
    {
        return !inS[p.first] || a[p.first] != p.second;
    }
    inline TPair Top()
    {
        while (!pq.empty() && Invalid(pq.top())) pq.pop();
        if (pq.empty()) return {-1, -1};
        return pq.top();
    }
};

struct ComparerMax
{
    bool operator()(const TPair& x, const TPair& y)
    {
        return x.second < y.second;
    }
};
struct ComparerMin
{
    bool operator()(const TPair& x, const TPair& y)
    {
        return x.second > y.second;
    }
};
THeap<ComparerMax> HeapMax;
THeap<ComparerMin> HeapMin;

int main()
{
    #ifdef Bang
    auto start = chrono::steady_clock::now();
    #endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen(taskname".inp", "r", stdin);
    freopen(taskname".out", "w", stdout);

    #ifdef Bang
    auto end = chrono::steady_clock::now();
    cerr << "In milliseconds : "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cerr << '\n' << "In seconds : "
         << chrono::duration_cast<chrono::seconds>(end - start).count() << '\n';
    #endif
    return 0;
}


