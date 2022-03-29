#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
int normN,normM;
class DinicFlow
{
public:
    int N, source, sink;
    //vector<vector<Edge *>> adj;
    vector<vector<int>> g;
    vector<vector<int>>cp,flw;
    //vector<vector<int>>fl;

    vector<pi> edges;
    vector<int> level;
    vector<int> work;
    DinicFlow() : N(0), source(0), sink(0), level(), work(), g(), cp() {}
    DinicFlow(const DinicFlow &df) : N(df.N), source(df.source), sink(df.sink), level(df.level), work(df.work), g(df.g), cp(df.cp) ,flw(df.flw){}
    DinicFlow(int N, int source, int sink) : N(N), source(source), sink(sink), level(N), work(N), g(N,vector<int>()), cp(N,vector<int>(N)),flw(N,vector<int>(N)) {}

    void add_edge(int from, int to, int cap)
    {
        // Edge *e = new Edge(from, to, cap);
        // Edge *e_reverse = new Edge(to, from, 0);
        // e->reverse = e_reverse;
        // e_reverse->reverse = e;
        // adj[from].push_back(e);
        // adj[to].push_back(e_reverse);
        g[from].push_back(to);
        g[to].push_back(from);
        cp[from][to]+=cap;
        edges.push_back({from,to});
    }

    bool levelling()
    {
        level=vector<int>(N,-1);
        level[source] = 0;
        queue<int> bq;
        bq.push(source);
        while (!bq.empty())
        {
            int now = bq.front();
            bq.pop();
            for (auto nx : g[now])
            {
                if (level[nx] == -1 && cp[now][nx]-flw[now][nx] > 0)
                {
                    level[nx] = level[now] + 1;
                    bq.push(nx);
                }
            }
        }
        return (level[sink] != -1);
    }

    int dfs(int cx, int mf)
    {
        if (cx == sink)
        {
            return mf;
        };

        for(int &i = work[cx]; i < g[cx].size(); i++)
        {
            int nx = g[cx][i];
            if (level[nx] == level[cx] + 1 && cp[cx][nx]-flw[cx][nx] > 0)
            {
                int flow = dfs(nx, min(mf, cp[cx][nx]-flw[cx][nx]));
                if (flow)
                {
                    flw[cx][nx]+=flow;
                    flw[nx][cx]-=flow;
                    return flow;
                }
            }
        }
        return 0;
    }

    int max_flow()
    {
        int ret = 0;
        while (levelling())
        {
            work=vector<int>(N);
            int flow=0;
            while(flow=dfs(source,INT_MAX))
                ret += flow;
        }
        return ret;
    }
    // ~DinicFlow(){
    //     for(auto &i : adj){
    //         for(auto &e : i){
    //             delete e;
    //         }
    //     }
    // }

    void change(int from, int to){
        vector<int> nxt(N+1,-1);
        queue<int> q;q.push(from);
        while(q.size()&&nxt[to]==-1){
            int cx=q.front();q.pop();
            for(int i = 0; i < g[cx].size(); i++){
                int nx = g[cx][i];
                if(cx<from||(cx==from&&nx<to))continue;
                if(cp[cx][nx]-flw[cx][nx]>0&&nxt[nx]==-1){
                    q.push(nx);
                    nxt[nx]=cx;
                }
            }
        }
        if(nxt[to]==-1)return;
        flw[from][to]=flw[to][from]=0;
        for(int i = to; i != from; i=nxt[i]){
            flw[nxt[i]][i]++;flw[i][nxt[i]]--;
        }
    }
    void sol(){
        for(int i = 1; i <= normN; i++){
            for(int j = 1; j <= normM; j++){
                if(flw[i][normN+j]!=1)continue;
                change(i,normN+j);
            }
        }
        for(int i = 1; i <= normN; i++){
            for(int j = 1; j <= normM; j++){
                cout << (bool)flw[i][normN+j];
            }
            cout << '\n';
        }
    }
};
const int INF = 1e9;
int N,source,sink,M;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>N>>M;
    normN=N;normM=M;
    source=0;sink=N*M+2;
    DinicFlow df(N*M+3,source,sink);
    int asum=0,bsum=0;
    int a,b;
    for(int i = 0; i < N; i++){
        cin>>a;
        asum+=a;
        df.add_edge(source,i+1,a);
        for(int j = 1; j <= M; j++){
            df.add_edge(i+1, N+j, 1);
        }
    }
    for(int j = 0; j < M; j++){
        cin>>b;bsum+=b;
        df.add_edge(N+j+1,sink,b);
    }
    if(asum!=bsum){cout<<-1;return 0;}


    if(df.max_flow()<asum){cout<<-1;return 0;}
    df.sol();
}