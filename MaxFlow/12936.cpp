#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using ll = long long;
int normN;
class Edge{
    public:
    int from,to,cap,flow;
    Edge *reverse;
    Edge():from(0),to(0),cap(0),flow(0),reverse(nullptr){}
    Edge(const Edge& e):from(e.from),to(e.to),cap(e.cap),flow(e.flow),reverse(e.reverse){}
    Edge(int from, int to, int cap):from(from),to(to),cap(cap),flow(0),reverse(nullptr){}

};
class DinicFlow
{
public:
    int N, source, sink;
    vector<vector<Edge *>> adj;
    vector<int> level;
    queue<int> bq;
    vector<int> work;
    DinicFlow() : N(0), source(0), sink(0), adj(), level(), bq(), work() {}
    DinicFlow(const DinicFlow &df) : N(df.N), source(df.source), sink(df.sink), adj(df.adj), level(df.level), bq(df.bq), work(df.work) {}
    DinicFlow(int N, int source, int sink) : N(N), source(source), sink(sink), adj(N), level(N), bq(), work(N) {}

    void add_edge(int from, int to, int cap)
    {
        Edge *e = new Edge(from, to, cap);
        Edge *e_reverse = new Edge(to, from, 0);
        e->reverse = e_reverse;
        e_reverse->reverse = e;
        adj[from].push_back(e);
        adj[to].push_back(e_reverse);
    }

    bool levelling()
    {
        level=vector<int>(N,-1);
        level[source] = 0;
        bq=queue<int>();
        bq.push(source);
        while (!bq.empty())
        {
            int now = bq.front();
            bq.pop();
            for (auto e : adj[now])
            {
                if (level[e->to] == -1 && e->cap > 0)
                {
                    level[e->to] = level[now] + 1;
                    bq.push(e->to);
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

        for(int &i = work[cx]; i < adj[cx].size(); i++)
        {
            auto e=adj[cx][i];
            if (level[e->to] == level[cx] + 1 && e->cap > 0)
            {
                int flow = dfs(e->to, min(mf, e->cap));
                if (flow)
                {
                    e->cap-=flow;
                    e->reverse->cap+=flow;
                    e->flow += flow;
                    e->reverse->flow -= flow;
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
    ~DinicFlow(){
        for(auto &i : adj){
            for(auto &e : i){
                delete e;
            }
        }
    }
};
const int INF = 1e9+7;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, M;

    cin >> N >> M;
    normN=N;

    int source = 0, sink = N + M + 2;
    DinicFlow df(N + M + 3, source, sink);
    for(int i = 0; i < N; i++){
        int a;
        cin >> a;
        df.add_edge(source,i+1,a);
        
    }
    int csum=0;
    for (int i = 1; i <= M; i++)
    {
        int a,b,c;
        cin>>a>>b>>c;
        csum+=c;
        df.add_edge(a,N+i,INF);
        df.add_edge(b,N+i,INF);
        df.add_edge(N+i,sink,c);
    
    }
    int res = df.max_flow();
    cout<<csum-res;
}