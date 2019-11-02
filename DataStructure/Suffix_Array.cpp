#include <iostream>
#include <cstdio>
#include <iomanip>
#include <chrono>
#include <algorithm>
#define pb push_back
#define Kami
#define taskname "SUBSTR"

using namespace std;
const int maxn=1e5+2;

int n,sa[maxn],lcp[maxn];
string s;

inline void Enter(){
    cin>>s;
    s.pb('@');
    n=s.size();
}

inline void BuildSuffixArray(){
    int *sb=new int[n],*key=new int[n],*head=new int[n];
    bool *mark=new bool[n];
    for(int i=0;i<n;i++) sa[i]=i;
    sort(sa,sa+n,[](const int &i, const int &j){
        return s[i]<s[j];
    });
    mark[0]=false;
    for(int i=1;i<n;i++) mark[i]=s[sa[i]]!=s[sa[i-1]];
    for(int k=1;k<n;k*=2){
        int nKey=0;
        head[0]=0;
        for(int i=0;i<n;i++){
            if(mark[i]) head[++nKey]=i;
            key[sa[i]]=nKey;
        }
        if(nKey==n-1) break;
        for(int i=0;i<n;i++) sb[i]=(sa[i]-k+n)%n;
        for(int i=0;i<n;i++) sa[head[key[sb[i]]]++]=sb[i];
        for(int i=1;i<n;i++) mark[i]|=key[(sa[i]+k)%n]!=key[(sa[i-1]+k)%n];
    }
}

inline void BuildLCP(){
    int *rnk=new int[n];
    for(int i=0;i<n;i++) rnk[sa[i]]=i;
    lcp[0]=0;
    for(int i=0,q=0;i<n-1;i++){
        int j=sa[rnk[i]-1];
        while(s[i+q]==s[j+q]) q++;
        lcp[rnk[i]]=q;
        if(q) q--;
    }
}

inline void Init(){
    BuildSuffixArray();
    BuildLCP();
}

inline void Solve(){
    long long sumLCP=0;
    for(int i=0;i<n;i++) sumLCP+=lcp[i];
    cout<<1ll*n*(n-1)/2-sumLCP;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL); if(fopen(taskname".INP","r"))
    freopen(taskname".INP","r",stdin),
    freopen(taskname".OUT","w",stdout);
    #ifdef Kami
    auto start=chrono::steady_clock::now();
    #endif

    Enter();
    Init();
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
