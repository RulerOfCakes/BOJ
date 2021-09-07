#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using ll = long long;

class Edge
{
public:
    int from, to, cap, cost;
    Edge *reverse;
    Edge() : from(0), to(0), cap(0), cost(0), reverse(nullptr) {}
    Edge(const Edge &e) : from(e.from), to(e.to), cap(e.cap), cost(e.cost), reverse(e.reverse) {}
    Edge(int from, int to, int cap, int cost) : from(from), to(to), cap(cap), cost(cost), reverse(nullptr) {}
};
class MCMF
{
public:
    int N, source, sink;
    vector<vector<Edge *>> adj;
    vector<int> dist, inQ;
    vector<int> chk, work;
    MCMF(int N, int source, int sink) : N(N), source(source), sink(sink), adj(N), dist(N), inQ(N), chk(N), work(N) {}

    void add_edge(int from, int to, int cap, int cost)
    {
        Edge *e = new Edge(from, to, cap, cost);
        Edge *e_reverse = new Edge(to, from, 0, -cost);
        e->reverse = e_reverse;
        e_reverse->reverse = e;
        adj[from].push_back(e);
        adj[to].push_back(e_reverse);
    }

    bool SPFA(){
        fill(dist.begin(),dist.end(),1e9);
        fill(inQ.begin(),inQ.end(),0);
        queue<int> q;
        q.push(source);
        inQ[source]=1;
        dist[source]=0;
        while(!q.empty()){
            int nx=q.front();
            q.pop();
            inQ[nx]=0;
            for(auto e : adj[nx]){
                if(e->cap&&dist[e->to]>dist[nx]+e->cost){
                    dist[e->to]=dist[nx]+e->cost;
                    if(!inQ[e->to])inQ[e->to]=1,q.push(e->to);
                }
            }
        }
        return dist[sink]<1e9;
    }

    int dfs(int cx, int mf)
    {
        chk[cx]=1;
        if (cx == sink)
            return mf;

        for (int& i = work[cx]; i<adj[cx].size(); i++)
        {
            auto& p = adj[cx][i];
            if(!chk[p->to]&&dist[p->to]==dist[cx]+p->cost && p->cap){
                int flow = dfs(p->to, min(mf,p->cap));
                if(flow){
                    p->cap-=flow;
                    p->reverse->cap+=flow;
                    return flow;
                }
            }
        }
        return 0;
    }

    pi run(){
        int cost=0,flow=0;
        while(SPFA()){
            fill(chk.begin(),chk.end(),0);
            fill(work.begin(),work.end(),0);
            int nx=0;
            while(nx=dfs(source,1e9)){
                cost+=dist[sink]*nx;
                flow+=nx;
                fill(chk.begin(),chk.end(),0);
            }
        }
        return pi(cost,flow);
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, M;
    cin >> N >> M;
    int source = 0, sink = N + M + 2;
    MCMF mf(N + M + 3, source, sink);
    vector<int> A(N+1),B(M+1);
    for(int i = 0; i < N; i++){
        cin >> A[i+1];
    }
    for(int i = 0; i < M; i++){
        cin >> B[i+1];
    }
    vector<vector<int>> C(M+1,vector<int>(N+1)),D(M+1,vector<int>(N+1));
    for(int i = 1; i <= M; i++){
        for(int j = 1; j <= N; j++){
            cin >> C[i][j];
        }
    }
    for(int i = 1; i <= M; i++){
        mf.add_edge(source, i, B[i], 0);
        for(int j = 1; j <= N; j++){
            int a;
            cin >> a;
            mf.add_edge(i,j+M,C[i][j],a);
        }
    }
    
    for (int i = 1; i <= N; i++)
    {
        mf.add_edge(i+M,sink,A[i],0);
    }
    pi p = mf.run();
    cout << p.second << '\n' << p.first;
}