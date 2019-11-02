typedef struct TIT* PIT;
struct TIT
{
    ll Max, lazy;
    PIT left, right;
    inline TIT(int l, int r)
    {
        Max = lazy = 0;
        if (l == r) return;
        int m = l + r >> 1;
        left = new TIT(l, m); right = new TIT(m + 1, r);
    }
    inline void Increase(ll x) { lazy += x; Max += x; }
    inline void PushDown()
    { if (lazy) left->Increase(lazy), right->Increase(lazy), lazy = 0; }
    inline void Update(int l, int r)
    {
        if (l >= L && r <= R) { Increase(val); return; }
        PushDown();
        int m = l + r >> 1;
        if (L <= m && R >= l) left->Update(l, m);
        if (L <= r && R > m) right->Update(m + 1, r);
        Max = max(left->Max, right->Max);
    }
    inline ll Query(int l, int r)
    {
        if (l >= L && r <= R) return Max;
        PushDown();
        int m = l + r >> 1;
        ll res = 0;
        if (L <= m && R >= l) res = left->Query(l, m);
        if (L <= r && R > m) res = max(res, right->Query(m + 1, r));
        return res;
    }
};
//QMAX2_SPOJ
