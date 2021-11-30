#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;

class Edge{
    public:
    int from,to,cap,flow;
    int revid;
    Edge():from(0),to(0),cap(0),flow(0),revid(0){}
    Edge(const Edge& e):from(e.from),to(e.to),cap(e.cap),flow(e.flow),revid(e.revid){}
    Edge(int from, int to, int cap,int revid):from(from),to(to),cap(cap),flow(0),revid(revid){}
};
class DinicFlow{
    public:
    int N, source, sink;
    vector<vector<Edge>> adj;
    vector<int> level,work;
    queue<int> bq;

    DinicFlow():N(0),source(0),sink(0),adj(),level(),bq(){}
    DinicFlow(const DinicFlow& df):N(df.N),source(df.source),sink(df.sink),adj(df.adj),level(df.level),work(df.work),bq(df.bq){}
    DinicFlow(int N, int source, int sink):N(N),source(source),sink(sink),adj(N),level(N),work(N),bq(){}
    
    void add_edge(int from, int to, int cap){
        Edge e(from,to,cap,adj[to].size());
        Edge e_reverse(to,from,0,adj[from].size());
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
            for(const auto e: adj[now]){
                if(level[e.to]==-1&&e.cap-e.flow>0){
                    level[e.to]=level[now]+1;
                    bq.push(e.to);
                }
            }
        }
        return level[sink]!=-1;
    }

    int dfs(int cx, int mf){
        if(cx==sink)return mf;
        for(int &i = work[cx]; i < adj[cx].size(); i++){
            auto& e = adj[cx][i];
            if(level[e.to]==level[cx]+1&&e.cap-e.flow>0){
                int flow=dfs(e.to,min(mf,e.cap-e.flow));
                if(flow>0){
                    e.flow+=flow;
                    adj[e.to][e.revid].flow-=flow;
                    return flow;
                }
            }
        }
        return 0;
    }

    int max_flow(){
        int ret=0;
        while(levelling()){
            fill(work.begin(),work.end(),0);
            int flow=0;
            while(flow=dfs(source,INT_MAX))
                ret+=flow;
        }
        return ret;
    }
};
const int INF = 1e9;
int T,N,source,sink,M;
int dx[]={0,0,-1,1};
int dy[]={1,-1,0,0};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> T;
    while(T--){
        cin >> N >> M;
        int sum=0;
        vector<vector<int>> v(N,vector<int>(M));
        vector<int>sv(N*M);
        for(int i = 0; i < N; i++){
            for(int j = 0; j < M; j++){
                cin >> v[i][j];
                sv[i*M+j]=v[i][j];
                sum+=v[i][j];
            }
        }
        source=N*M,sink=N*M+1;
        DinicFlow df(N*M+2, N*M, N*M+1);
        for(int i = 0; i < N*M; i++){
            int cx=i/M,cy=i%M;
            if((cx+cy)%2){
                //to sink
                df.add_edge(i,sink,sv[i]);
            }
            else{
                //from source
                df.add_edge(source,i,sv[i]);
                for(int k = 0; k < 4; k++){
                    int nx=cx+dx[k],ny=cy+dy[k];
                    if(nx<0||nx>=N||ny<0||ny>=M)continue;
                    int ni = nx*M+ny;
                    df.add_edge(i,ni,INF);
                }
            }
        }
        cout << sum-df.max_flow() << '\n';
    }
}