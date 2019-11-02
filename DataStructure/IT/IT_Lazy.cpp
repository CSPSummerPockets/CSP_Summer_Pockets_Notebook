int n, m, L, R, val;
#define m (l + r >> 1)
typedef struct TIT* PIT;
struct TIT
{
    ll Max, lazy;
    PIT left, right;
    inline TIT(int l, int r)
    {
        Max = lazy = 0;
        if (l == r) return;
        left = new TIT(l, m); right = new TIT(m + 1, r);
    }
    #define PushDown if (lazy) { Max += lazy; if (l != r) left->lazy += lazy, right->lazy += lazy; lazy = 0; }
    inline void Update(int l, int r)
    {
        PushDown;
        if (l > R || r < L) return;
        if (l >= L && r <= R) { lazy += val; PushDown; return; }
        left->Update(l, m); right->Update(m + 1, r);
        Max = max(left->Max, right->Max);
    }
    inline ll Query(int l, int r)
    {
        PushDown;
        if (l > R || r < L) return 0;
        if (l >= L && r <= R) return Max;
        return max(left->Query(l, m), right->Query(m + 1, r));
    }
};
//QMAX2_SPOJ
