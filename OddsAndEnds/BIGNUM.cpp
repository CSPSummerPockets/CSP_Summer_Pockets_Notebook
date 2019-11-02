#include<bits/stdc++.h>

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

using namespace std;

#define d (*this)
const int LEN = 9;
const ll Radix = pow(10, LEN);
struct TBigNum : public deque<ll>
{
    inline TBigNum() { assign(1, 0); }
    inline TBigNum& Refine() { while (size() > 1 && back() == 0) pop_back(); return d; }
    inline TBigNum& operator = (ll x)
    { for (clear(); x > 0; x /= Radix) push_back(x % Radix); return d; }
    inline TBigNum& operator = (const string& s)
    {
        assign(s.size() / LEN + 1, 0);
        for (int i = 0, pos; i < s.size(); ++i)
        {
            pos = (s.size() - i - 1) / LEN;
            d[pos] = d[pos] * 10 + s[i] - '0';
        }
        return Refine();
    }
    inline TBigNum& Fix()
    {
        push_back(0);
        for (auto it = begin(); it < end() - 1; ++it)
        {
            *(it + 1) += *it / Radix;
            *it %= Radix;
        }
        return Refine();
    }

    inline TBigNum& operator += (const TBigNum &t)
    {
        resize(max(size(), t.size()) + 1, 0);
        for (int i = 0; i < t.size(); ++i)
            if ((d[i] += t[i]) >= Radix) ++d[i + 1], d[i] -= Radix;
        return Refine();
    }
    inline TBigNum& operator -= (const TBigNum &t)
    {
        for (int i = 0; i < t.size(); ++i)
            if ((d[i] -= t[i]) < 0) --d[i + 1], d[i] += Radix;
        return Refine();
    }
    inline TBigNum& Mul(const TBigNum &a, ll b)
    {
        resize(a.size() + 1);
        d[0] = 0;
        for (int i = 0; i < a.size(); ++i)
        {
            ll val = d[i] + a[i] * b;
            d[i + 1] = val / Radix;
            d[i] = val - d[i + 1] * Radix;
        }
        return Refine();
    }
    inline TBigNum& Mul(const TBigNum &a, const TBigNum &b)
    {
        assign(a.size() + b.size() + 1, 0);
        for (int i = 0, j; i < a.size(); ++i)
        {
            ll carry = 0, val;
            for (j = 0; j < b.size(); ++j)
            {
                val = d[i + j] + carry + a[i] * b[j];
                carry = val / Radix;
                d[i + j] = val - carry * Radix;
            }
            for (; carry > 0; ++j)
            {
                val = d[i + j] + carry;
                carry = val / Radix;
                d[i + j] = val - carry * Radix;
            }
        }
        return Refine();
    }
    inline TBigNum& Divide(const TBigNum &a, int b, ll &r)
    {
        clear(); r = 0;
        for (auto it = a.rbegin(); it != a.rend(); ++it)
        {
            r = r * Radix + *it;
            push_front(r / b);
            r %= b;
        }
        return Fix();
    }
    inline int operator % (int b) const &
    {
        ll r = 0;
        for (auto it = rbegin(); it != rend(); ++it) r = (r * Radix + *it) % b;
        return r;
    }
    inline TBigNum& Divide(const TBigNum&, const TBigNum&, TBigNum&);
    inline TBigNum& Sqrt(const TBigNum &);
} INTMAX, One, Zero;

inline ll LLI(const TBigNum &a)
{
    ll res = 0;
    for (auto it = a.rbegin(); it != a.rend(); ++it) res = res * Radix + *it;
    return res;
}

inline istream& operator >> (istream& cin, TBigNum &a)
{
    string s;
    cin >> s;
    a = s;
    return cin;
}
inline ostream& operator << (ostream& cout, const TBigNum &a)
{
    cout << a.back();
    for (auto it = a.rbegin() + 1; it < a.rend(); ++it)
        cout << setw(LEN) << setfill('0') << *it;
    return cout;
}

inline int Compare(const TBigNum& a, const TBigNum &b)
{
    if (a.size() != b.size()) return a.size() - b.size();
    for (int i = a.size() - 1; i >= 0; --i)
        if (a[i] != b[i]) return a[i] - b[i];
    return 0;
}
#define OP(x) inline bool operator x (const TBigNum& a, const TBigNum& b) { return Compare(a, b) x 0; }
OP(==); OP(!=); OP(>); OP(<); OP(>=); OP(<=);
#undef OP

inline TBigNum& TBigNum::Divide(const TBigNum& a, const TBigNum& b, TBigNum& r)
{
    if (b <= INTMAX)
    {
        ll tmp;
        Divide(a, LLI(b), tmp);
        r = tmp;
        return d;
    }
    TBigNum tmp;
    clear(); r.clear();
    for (auto it = a.rbegin(); it != a.rend(); ++it)
    {
        r.push_front(*it);
        if (r < b) {push_front(0); continue;}
        int low = 2, high = Radix - 1, mid; //quotient in (0, Radix)
        while (low <= high)
        {
            mid = low + high >> 1;
            tmp.Mul(b, mid);
            int x = Compare(tmp, r);
            if (x > 0) high = mid - 1;
            else if (x == 0) high = mid, low = mid + 1;
            else low = mid + 1;
        }
        push_front(high);
        r -= tmp.Mul(b, high);
    }
    return Refine();
}

inline TBigNum& TBigNum::Sqrt(const TBigNum &a)
{
    d = a;
    ll r;
    TBigNum x, t = a, t1, r1;
    x.Divide(t += One, 2, r); // x = (a + 1) / 2
    while (x < d)
    {
        d = x;
        t = a; t1.Divide(t, x, r1);
        t = x; x.Divide(t += t1, 2, r); // x = (x + a / x) / 2
    }
    return d;
}
#undef d

int main()
{
    //freopen("TEST.inp", "r", stdin);
    //freopen("TEST.out", "w", stdout);
    INTMAX = INT_MAX;
    TBigNum a, b, c, d;
    cin >> a >> b;
    c = a; cout << (c += b) << '\n';
    if (a >= b) c = a, cout << (c -= b) << '\n';
    else c = b, cout << '-' << (c -= a) << '\n';
    cout << c.Mul(a, b);
}
