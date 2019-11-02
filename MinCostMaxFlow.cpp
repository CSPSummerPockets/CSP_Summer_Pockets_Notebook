template<typename FlowType, typename CostType> class MinCostMaxFlow{
public:
    struct TEdges{
        int x,y;
        FlowType cap,flow;
        CostType cost;
        inline TEdges(int _x=0, int _y=0, FlowType _cap=0, CostType _cost=0, FlowType _flow=0){
            x=_x; y=_y; cap=_cap; cost=_cost; flow=_flow;
        }
    };
    int n,source,sink;
    bool aldreadyUsedMaxFlow,aldreadyUsedMinCost;
    FlowType flowVal;
    CostType costVal;
    vector<TEdges> e;
    vector<int> trace;
    vector<bool> inQueue;
    vector<CostType> d;
    vector<vector<int> >adj;
 
    inline MinCostMaxFlow(int _n, int _source, int _sink){
        n=_n; source=_source; sink=_sink;
        aldreadyUsedMaxFlow=aldreadyUsedMinCost=false;
        flowVal=0; costVal=0; inQueue.resize(n);
        trace.resize(n); adj.resize(n); d.resize(n);
    }
 
    inline void AddEdge(const int &u, const int &v, const FlowType &cap, const CostType &cost){
        adj[u].push_back(e.size());
        e.push_back(TEdges(u,v,cap,cost));
        adj[v].push_back(e.size());
        e.push_back(TEdges(v,u,0,-cost));
    }
 
    inline bool FindPath(){
        fill(trace.begin(),trace.end(),-1);
        fill(d.begin(),d.end(),numeric_limits<CostType>::max());
        fill(inQueue.begin(),inQueue.end(),false);
        queue<int> q;
        q.push(source); inQueue[source]=true; d[source]=0; trace[source]=-2;
        while(q.size()){
            int u=q.front(); inQueue[u]=false;
            q.pop();
            for(int i: adj[u]) if(e[i].cap>0){
                int v=e[i].y;
                int w=e[i].cost;
                if(d[v]>d[u]+w){
                    d[v]=d[u]+w;
                    trace[v]=i;
                    if(!inQueue[v]){
                        q.push(v);
                        inQueue[v]=true;
                    }
                }
            }
        }
        return trace[sink]!=-1;
    }
 
    inline void AugmentFlow(){
        FlowType delta=numeric_limits<FlowType>::max();
        for(int u=sink,i;(i=trace[u])>=0;u=e[i].x) delta=min(delta,e[i].cap);
        for(int u=sink,i;(i=trace[u])>=0;u=e[i].x){
            e[i].cap-=delta;
            e[i^1].cap+=delta;
            e[i].flow+=delta;
            e[i^1].flow-=delta;
        }
        flowVal+=delta;
        costVal+=d[sink]*delta;
    }
 
    inline FlowType MaxFlow(){
        if(aldreadyUsedMaxFlow) return flowVal;
        aldreadyUsedMaxFlow=true;
        while(FindPath()) AugmentFlow();
        return flowVal;
    }
 
    inline CostType MinCost(){
        if(aldreadyUsedMinCost) return costVal;
        aldreadyUsedMinCost=true; MaxFlow();
        return costVal;
    }
};