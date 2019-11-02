#include <bits/stdc++.h>
#define taskname "TEST"

//#define BeztDonkey
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

using namespace std;

const int maxN = 1e5 + 9;

const int nMods = 2;
const int Mods[] = {int(1e9 + 7), int(1e9 + 9)};
struct THash
{
    int val[nMods];
    inline THash() {}
    inline THash(int x)
    {
        for (int i = 0; i < nMods; ++i) val[i] = x;
    }
    inline THash operator * (const THash& other) const &
    {
        THash res;
        for (int i = 0; i < nMods; ++i)
            res.val[i] = (ll)val[i] * other.val[i] % Mods[i];
        return res;
    }
    inline THash operator * (const int other) const &
    {
        THash res;
        for (int i = 0; i < nMods; ++i)
            res.val[i] = (ll)val[i] * other % Mods[i];
        return res;
    }
    inline THash operator + (const int other) const &
    {
        THash res;
        for (int i = 0; i < nMods; ++i)
            res.val[i] = (val[i] + other) % Mods[i];
        return res;
    }
    inline THash operator - (const THash& other) const &
    {
        THash res;
        for (int i = 0; i < nMods; ++i)
            res.val[i] = (val[i] - other.val[i] + Mods[i]) % Mods[i];
        return res;
    }
    inline bool operator == (const THash& other) const &
    {
        for (int i = 0; i < nMods; ++i)
            if (val[i] != other.val[i]) return 0;
        return 1;
    }
} p[maxN], Hs[maxN], Ht[maxN];
string s, t;
int n, m, q, x, y, u, v;

void Init()
{
    const static int BASE = 653;
    p[0] = 1;
    for (int i = 1; i <= n; ++i) p[i] = p[i - 1] * BASE;
    Hs[0] = 0;
    for (int i = 1; i <= n; ++i) Hs[i] = Hs[i - 1] * BASE + s[i];
    Ht[0] = 0;
    for (int i = 1; i <= m; ++i) Ht[i] = Ht[i - 1] * BASE + t[i];
}
inline THash GetS(int l, int r)
{
    return Hs[r] - Hs[l - 1] * p[r - l + 1];
}
inline THash GetT(int l, int r)
{
    return Ht[r] - Ht[l - 1] * p[r - l + 1];
}

struct THashTable
{
	const static int mod = 2e6 + 7;
	int len = -1;
	struct TNode
	{
		unsigned key;
		int id;
		TNode *Next;
	} nodes[mod], *head[mod];
	inline int GetId(unsigned key)
	{
		int hkey = key % mod;
		for (TNode* e = head[hkey]; e != NULL; e = e->Next)
            if (e->key == key) return e->id;
        nodes[++len] = {key, len, head[hkey]};
        head[hkey] = &nodes[len];
        return len;
	}
} HashTable;

int main()
{
    #ifdef BeztDonkey
    auto start = chrono::steady_clock::now();
    #endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen(taskname".inp", "r", stdin);
    freopen(taskname".out", "w", stdout);

    return 0;

}
