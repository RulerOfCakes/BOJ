#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using ll = long long;
int normN;
// class Edge{
//     public:
//     int from,to,cap,flow;
//     Edge *reverse;
//     Edge():from(0),to(0),cap(0),flow(0),reverse(nullptr){}
//     Edge(const Edge& e):from(e.from),to(e.to),cap(e.cap),flow(e.flow),reverse(e.reverse){}
//     Edge(int from, int to, int cap):from(from),to(to),cap(cap),flow(0),reverse(nullptr){}
// };

class DinicFlow
{
public:
    int N, source, sink;
    //vector<vector<Edge *>> adj;
    vector<vector<int>> g;
    vector<vector<int>>cp;
    //vector<vector<int>>fl;

    vector<pi> edges;
    vector<int> level;
    vector<int> work;
    DinicFlow() : N(0), source(0), sink(0), level(), work(), g(), cp() {}
    DinicFlow(const DinicFlow &df) : N(df.N), source(df.source), sink(df.sink), level(df.level), work(df.work), g(df.g), cp(df.cp) {}
    DinicFlow(int N, int source, int sink) : N(N), source(source), sink(sink), level(N), work(N), g(N,vector<int>()), cp(N,vector<int>(N)) {}

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
                if (level[nx] == -1 && cp[now][nx] > 0)
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
            if (level[nx] == level[cx] + 1 && cp[cx][nx] > 0)
            {
                int flow = dfs(nx, min(mf, cp[cx][nx]));
                if (flow)
                {
                    cp[cx][nx]-=flow;
                    cp[nx][cx]+=flow;
                    
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

    void sol(){
        int ans = 0;
        vector<vector<int>> d(N,vector<int>(N));
        for(int i = 1; i <= normN; i++){
            for(auto nxt: g[i]){
                if(cp[i][nxt]>0)d[i][nxt]=1;
            }
        }
        for(int i = 1; i <= normN; i++){
            for(int j = 1; j <= normN; j++){
                for(int k = 1; k <= normN; k++){
                    if(d[j][i]&&d[i][k]){
                        d[j][k]=1;
                    }
                }
            }
        }
        for(auto nxt: edges){
            if(!d[nxt.first][nxt.second])ans++;
        }
        cout << ans << '\n';
    }
};
const int INF = 1e9+7;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int K;
    cin >> K;
    while(K--){
        int N, M;

        cin >> N >> M;
        normN=N;

        int source = 1, sink = N;
        DinicFlow df(N + 1, source, sink);
        for(int i = 0; i < M; i++){
            int a,b,c;
            cin >> a >> b >> c;
            df.add_edge(a,b,c);
        }
        
        
        df.max_flow();
        df.sol();
    }
}