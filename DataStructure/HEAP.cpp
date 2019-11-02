#include <bits/stdc++.h>
using namespace std;
const int maxN= 1e5+ 9;

typedef bool BetterFunc(int x, int y);

struct THeap
{
    bool (*better)(int, int);
    int item[maxN], pos[maxN], nItems;
    void Init(BetterFunc bf)
    {
        better = bf;
        fill(pos, pos + maxN, 0);
        nItems = 0;
    }
    int Get()
    {
        return item[1];
    }
    void UpHeap(int c)
    {
        int x = item[c], p;
        do
        {
            p = c >> 1;
            if (p == 0 || !better(a[x], a[item[p]])) break;
            item[c] = item[p];
            pos[item[c]] = c;
            c = p;
        }
        while (true);
        item[c] = x;
        pos[x] = c;
    }
    void DownHeap(int p)
    {
        int x = item[p], c;
        do
        {
            c = p << 1;
            if (c < nItems && better(a[item[c + 1]], a[item[c]])) c++;
            if (c > nItems || !better(a[item[c]], a[x])) break;
            item[p] = item[c];
            pos[item[p]] = p;
            p = c;
        }
        while (true);
        item[p] = x;
        pos[x] = p;
    }
    void Change(int i, int k)
    {
        int oldval = a[i];
        a[i] = k;
        if (better(k, oldval))
            UpHeap(pos[i]);
        else
            DownHeap(pos[i]);
    }
    void Insert(int i)
    {
        nItems++;
        item[nItems] = i;
        pos[i] = nItems;
        UpHeap(nItems);
    }
    void Extract()
    {
        pos[item[1]] = 0;
        item[1] = item[nItems];
        pos[item[1]] = 1;
        nItems--;
        DownHeap(1);
    }
    void Pop(int x)
    {
         int y = item[nItems--];
         int i = pos[x];
         pos[x] = 0;
         if (nItems == 0) return;
         item[i] = y;
         pos[y] = i;
         better(a[x], a[y]) ? DownHeap(i) : UpHeap(i);
         pos[x]= 0;
    }
};

bool MaxBetter(int i, int j)
{
    return i > j;
}

THeap HeapMax, HeapMin;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
}
