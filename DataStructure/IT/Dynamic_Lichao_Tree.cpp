typedef pair<long long,long long> TLine;
const int maxn=1e5+7;
const int inf=1e9+7;
 
struct TLiChao{
    int l,r;
    TLine curLine;
    TLiChao *left,*right;
    inline TLiChao(int _l=0, int _r=0){
        l=_l; r=_r;
        curLine=TLine(inf,inf);
        left=right=NULL;
    }
}*root;
 
inline long long F(const TLine &d, const int &x){
    return d.first*x+d.second;
}
 
inline void Build(const int &l, const int &r){
    root=new TLiChao(l,r);
}
 
inline void Insert(TLine newLine, TLiChao* node=root){
    int l=node->l, r=node->r;
    TLine curLine=node->curLine;
    int m=l+r>>1;
    bool lef=(F(newLine,l)<F(curLine,l));
    bool mid=(F(newLine,m+1)<F(curLine,m+1));
    if(mid) swap(node->curLine,newLine);
    if(l==r) return;
    if(lef==mid){
        if(!node->right) node->right=new TLiChao(m+1,r);
        Insert(newLine,node->right);
    } else{
        if(!node->left) node->left=new TLiChao(l,m);
        Insert(newLine,node->left);
    }
}
 
inline long long Get(const int &x, TLiChao* node=root){
    int mid=node->l+node->r>>1;
    if(node->l==node->r) return F(node->curLine,x);
    if(x<=mid){
        if(!node->left) return F(node->curLine,x);
        return min(F(node->curLine,x),Get(x,node->left));
    }
    if(!node->right) return F(node->curLine,x);
    return min(F(node->curLine,x),Get(x,node->right));
}