#include <iostream>
#include <cstdio>
#include <set>
#include <algorithm>
#define CL(x) (x<<1)
#define CR(x) (x<<1|1)
#define taskname "TEST"
using namespace std;
typedef pair<long long,long long> TLine;
const int maxn=1e5+7;
const long long inf=1e18;
 
int n;
int l[4*maxn],r[4*maxn];
TLine it[4*maxn];
 
inline void Build(const int &x, const int &low, const int &high){
    if(low>high) return;
    l[x]=low; r[x]=high;
    if(low==high) it[x]=TLine(0,-inf);
    else{
        int mid=low+high>>1;
        Build(CL(x),low,mid);
        Build(CR(x),mid+1,high);
        it[x]=TLine(0,-inf);
    }
}
 
inline long long F(const TLine &d, const long long &x){
    return d.first*x+d.second;
}
 
inline void Insert(TLine newLine, const int &low, const int &high, int x=1){
    if(l[x]>high || r[x]<low) return;
    if(low<=l[x] && r[x]<=high){
        int m=l[x]+r[x]>>1;
        bool lef=(F(newLine,l[x])>F(it[x],l[x]));
        bool mid=(F(newLine,min(m+1,r[x]))>F(it[x],min(m+1,r[x])));
        if(mid) swap(newLine,it[x]);
        if(l[x]==r[x]) return;
        if(lef!=mid) Insert(newLine,low,high,CL(x));
        else Insert(newLine,low,high,CR(x));
    } else{
        Insert(newLine,low,high,CL(x));
        Insert(newLine,low,high,CR(x));
    }
}
 
inline long long Get(const int &pos, int x=1){
    int m=l[x]+r[x]>>1;
    if(l[x]==r[x]) return F(it[x],pos);
    if(pos<=m) return max(F(it[x],pos),Get(pos,CL(x)));
    return max(F(it[x],pos),Get(pos,CR(x)));
}