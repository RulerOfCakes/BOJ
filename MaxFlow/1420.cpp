#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;

int N,M;

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

char arr[102][102];
int dx[]={1,-1,0,0};
int dy[]={0,0,-1,1};
const int INF = 1e9;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> N >> M;
    int source,sink,x1,y1,x2,y2;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> arr[i][j];
            if(arr[i][j]=='K'){
                source=i*M+j;
                source*=2;
                x1=i;
                y1=j;
            }
            else if(arr[i][j]=='H'){
                sink=i*M+j;
                sink*=2;
                x2=i;
                y2=j;
            }
        }
    }
    if(abs(x1-x2)+abs(y1-y2)==1){
        cout << -1;
        return 0;
    }

    DinicFlow df(2*N*M+2,source+1,sink);
    for(int i = 0; i < N*M; i++){
        df.add_edge(i*2,i*2+1,1);
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            int cp = i*M+j;
            cp*=2;
            if(arr[i][j]=='#')continue;
            for(int k = 0; k < 4; k++){
                int nx = i+dx[k],ny = j+dy[k];
                if(nx<0||nx>=N||ny<0||ny>=M)continue;
                int np = nx*M+ny;
                np*=2;
                if(arr[nx][ny]=='#')continue;
                df.add_edge(cp+1,np,INF);
            }
        }
    }

    cout << df.max_flow();
}