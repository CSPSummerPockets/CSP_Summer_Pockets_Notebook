#include <iostream>
#include <cstdio>
#include <iomanip>
#include <chrono>
#include <vector>
#include <algorithm>
#define Kami
#define taskname "TEST"
using namespace std;
const int maxn=1e5+7;

struct Edges{
    int x,y,w;
};

int n,L,subSize[maxn],bit[maxn],d[maxn];
bool disabled[maxn];
long long res;
vector<int> adj[maxn],depthList,tobeProcessed;
Edges e[maxn];

template<typename T> inline void Read(T &x){
    register char c;
    bool neg=false;
    for(c=getchar();c<'0'||c>'9';c=getchar()) if(c=='-') neg=true;
    for(x=0;'0'<=c&&c<='9';c=getchar()) x=x*10+c-'0';
    if(neg) x=-x;
}template<typename T,typename... Args> inline void Read(T &x,Args&... args){
    Read(x);
    Read(args...);
}template<typename T> inline void Write(T x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) Write(x/10);
    putchar(x%10+'0');
}template<typename T> inline void Write(T x, const char &c){
    if(x<0) putchar('-'),x=-x;
    Write(x);
    putchar(c);
}template <typename T,typename... Args> inline void Write(const T &a, const char &c, Args... args){
    Write(a,c);
    Write(args...);
}

inline void Input(){
    Read(n,L);
    for(int i=1;i<n;i++){
        Read(e[i].x,e[i].y,e[i].w);
        adj[e[i].x].push_back(i);
        adj[e[i].y].push_back(i);
    }
}

inline void CalcSize(const int &u, const int &p){
    subSize[u]=1;
    for(int i: adj[u]){
        int v=e[i].x+e[i].y-u;
        if(v==p || disabled[v]) continue;
        CalcSize(v,u);
        subSize[u]+=subSize[v];
    }
}

inline int FindCentroid(int u){
    int halfSize=subSize[u]/2;
    while(true){
        int heavyVertex=-1;
        for(int i: adj[u]){
            int v=e[i].x+e[i].y-u;
            if(disabled[v] || subSize[v]>subSize[u]) continue;
            if(subSize[v]>halfSize){
                heavyVertex=v;
                break;
            }
        }
        if(heavyVertex==-1) break;
        u=heavyVertex;
    }
    return u;
}

inline void CalcDepth(const int &u, const int &p){
    if(d[u]>L) return;
    depthList.push_back(d[u]);
    for(int i: adj[u]){
        int v=e[i].x+e[i].y-u;
        if(v==p || disabled[v]) continue;
        d[v]=d[u]+e[i].w;
        CalcDepth(v,u);
    }
}

inline void Increment(int x){
    for(;x<=(int)depthList.size();x+=x&-x) bit[x]++;
}

inline int Get(int x){
    int cnt=0;
    for(;x;x-=x&-x) cnt+=bit[x];
    return cnt;
}

inline int Compress(const int &x){
    return upper_bound(depthList.begin(),depthList.end(),x)-depthList.begin();
}

inline void Query(const int &u, const int &p){
    if(d[u]>L) return;
    res+=Get(Compress(L-d[u]));
    for(int i: adj[u]){
        int v=e[i].x+e[i].y-u;
        if(v==p || disabled[v]) continue;
        Query(v,u);
    }
}

inline void Update(const int &u, const int &p){
    if(d[u]>L) return;
    Increment(Compress(d[u]));
    for(int i: adj[u]){
        int v=e[i].x+e[i].y-u;
        if(v==p || disabled[v]) continue;
        Update(v,u);
    }
}

inline void ProcessTree(int u){
    CalcSize(u,-1);
    u=FindCentroid(u);
    depthList.resize(0);
    d[u]=0;
    CalcDepth(u,-1);
    sort(depthList.begin(),depthList.end());
    fill(bit,bit+(int)depthList.size()+1,0);
    Increment(Compress(0));
    for(int i: adj[u]){
        int v=e[i].x+e[i].y-u;
        if(disabled[v]) continue;
        Query(v,u);
        Update(v,u);
        tobeProcessed.push_back(v);
    }
    disabled[u]=true;
}

inline void Solve(){
    depthList.reserve(n+3);
    for(tobeProcessed.push_back(1);tobeProcessed.size();){
        int u=tobeProcessed.back();
        tobeProcessed.pop_back();
        ProcessTree(u);
    }
    Write(res);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL); if(fopen(taskname".INP","r"))
    freopen(taskname".INP","r",stdin),
    freopen(taskname".OUT","w",stdout);
    #ifdef Kami
    auto start=chrono::steady_clock::now();
    #endif

    Input();
    Solve();

    #ifdef Kami
    auto end=chrono::steady_clock::now();
    cerr<<"\nIn milliseconds : "
        <<chrono::duration_cast<chrono::milliseconds>(end-start).count();
    cerr<<'\n'<<"In seconds : "<<fixed<<setprecision(3)
        <<(double)chrono::duration_cast<chrono::milliseconds>(end-start).count()/1000<<'\n';
    #endif

    return 0;
}
