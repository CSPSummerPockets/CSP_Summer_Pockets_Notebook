int pos, i, j;
struct TLine
{
    int x;
    ll y;
    inline TLine(int x = 0, ll y = 0) : x(x), y(y) {}
    inline ll Get(int pos) { return (ll)x * v[pos - 1] + y; }
};
struct TMaxIT
{
    int l, r, m;
    TMaxIT *left, *right;
    TLine cur;
    inline TMaxIT(int l = 0, int r = 0) : l(l), r(r)
    {
        m = l + r >> 1;
        if (l == r) return;
        left = new TMaxIT(l, m);
        right = new TMaxIT(m + 1, r);
    }
    inline void _Add(TLine val)
    {
        if (l >= i && r <= j)
        {
            ll lval = val.Get(l), lcur = cur.Get(l);
            ll rval = val.Get(r), rcur = cur.Get(r);
            if (lcur >= lval && rcur >= rval) return;
            if (lcur <= lval && rcur <= rval) { cur = val; return; }
            ll mval = val.Get(m), mcur = cur.Get(m);
            if (lcur >= lval && mcur >= mval) { right->_Add(val); return; }
            if (lcur <= lval && mcur <= mval) { right->_Add(cur); cur = val; return; }
            if (rcur >= rval && mcur >= mval) { left->_Add(val); return; }
            if (rcur <= rval && mcur <= mval) { left->_Add(cur); cur = val; return; }
            return;
        }
        if (l <= j && m >= i) left->_Add(val);
        if (m < j && r >= i) right->_Add(val);
    }
    inline void Add(int l, int r, const TLine &val) { if (l > r) return; i = l; j = r; _Add(val); }
    inline ll _Query()
    {
        if (l == r) return cur.Get(pos);
        if (pos <= m) return max(cur.Get(pos), left->_Query());
        return max(cur.Get(pos), right->_Query());
    }
    inline ll Query(int p) { pos = p; return _Query(); }
} MaxIT;

int main()
{
    Cin(n);
    m.resize(n);
    for (vector<TMush>::iterator it = m.begin(); it != m.end(); ++it) Cin(it->x), Cin(it->w), Cin(it->e), v.push_back(it->x);
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    MaxIT = TMaxIT(1, v.size());
    //fi = -wj * |xi - xj| + fj + ei
    ll ans = 0, f;
    for (vector<TMush>::iterator it = m.begin(); it != m.end(); ++it)
    {
        int pos = upper_bound(v.begin(), v.end(), it->x) - v.begin();
        f = MaxIT.Query(pos) + it->e;
        ans = max(ans, f);
        if (it->w)
        {
            MaxIT.Add(pos, upper_bound(v.begin(), v.end(), min(it->x + f / it->w, (ll)v.back())) - v.begin(), TLine(-it->w, it->w * (ll)it->x + f));
            MaxIT.Add(lower_bound(v.begin(), v.end(), max(it->x - f / it->w, (ll)v[0])) - v.begin() + 1, pos, TLine(it->w, -it->w * (ll)it->x + f));
        }
        {
            MaxIT.Add(pos, v.size(), TLine(-it->w, it->w * (ll)it->x + f));
            MaxIT.Add(1, pos, TLine(it->w, -it->w * (ll)it->x + f));
        }
    }
    cout << ans;
}
//VOMARIO_SPOJ
