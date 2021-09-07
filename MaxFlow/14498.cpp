#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;

class Edge{
    public:
    int from,to,cap,flow;
    Edge *reverse;
    Edge():from(0),to(0),cap(0),flow(0),reverse(nullptr){}
    Edge(const Edge& e):from(e.from),to(e.to),cap(e.cap),flow(e.flow),reverse(e.reverse){}
    Edge(int from, int to, int cap):from(from),to(to),cap(cap),flow(0),reverse(nullptr){}

};

class DinicFlow{
    public:
    int N, source, sink;
    vector<vector<Edge*>> adj;
    vector<int> level;
    queue<int> bq;

    DinicFlow():N(0),source(0),sink(0),adj(),level(),bq(){}
    DinicFlow(const DinicFlow& df):N(df.N),source(df.source),sink(df.sink),adj(df.adj),level(df.level),bq(df.bq){}
    DinicFlow(int N, int source, int sink):N(N),source(source),sink(sink),adj(N),level(N),bq(){}
    
    void add_edge(int from, int to, int cap){
        Edge* e = new Edge(from,to,cap);
        Edge* e_reverse = new Edge(to,from,0);
        e->reverse=e_reverse;
        e_reverse->reverse=e;
        adj[from].push_back(e);
        adj[to].push_back(e_reverse);
    }

    bool levelling(){
        fill(level.begin(),level.end(),-1);
        level[source]=0;
        bq.push(source);
        while(!bq.empty()){
            int now = bq.front();
            bq.pop();
            for(auto e: adj[now]){
                if(level[e->to]==-1&&e->cap-e->flow>0){
                    level[e->to]=level[now]+1;
                    bq.push(e->to);
                }
            }
        }
        return level[sink]!=-1;
    }

    int dfs(int cx, int mf){
        if(cx==sink)return mf;

        for(auto e:adj[cx]){
            if(level[e->to]==level[cx]+1&&e->cap-e->flow>0){
                int flow=dfs(e->to,min(mf,e->cap-e->flow));
                if(flow>0){
                    e->flow+=flow;
                    e->reverse->flow-=flow;
                    return flow;
                }
            }
        }
        return 0;
    }

    int max_flow(){
        int ret=0;
        while(levelling()){
            int flow=dfs(source,INT_MAX);
            if(flow==0)break;
            ret+=flow;
        }
        return ret;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    
    
        int C,D,V;
        
        cin >> C >> D >> V;

        int source=0, sink=V+1;
        DinicFlow df(V+2,source,sink);
        vector<pair<int,int>> tv(V+1);
        vector<bool> tgl(V+1);
        for (int i =1; i <= V; i++)
        {
            int a,b,c;
            cin >> a >> b >> c;
            tgl[i]=c>0;
            tv[i]={a,b};
            //df.add_edge(b,a,1);
        }
        for(int i = 1; i <= V; i++){
            if(!tgl[i])
                df.add_edge(source,i,1);
            else
                df.add_edge(i,sink,1);
                
            
            for(int j = i+1; j <= V; j++){
                if((tgl[i]!=tgl[j])&&(tv[i].first==tv[j].first||tv[j].second==tv[i].second)){
                    if(!tgl[i])
                        df.add_edge(i,j,1);
                    else
                        df.add_edge(j,i,1);
                }
            }
        }
        cout << df.max_flow() << '\n';
    
}