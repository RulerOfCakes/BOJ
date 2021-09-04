#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
const int INF = 1e9 + 7;
struct Edge{
    int from, to, cap, flow;
    Edge *reverse;
    Edge() : from(0), to(0), cap(0), flow(0), reverse(nullptr) {}
    Edge(const Edge &e) : from(e.from), to(e.to), cap(e.cap), flow(e.flow), reverse(e.reverse) {}
    Edge(int from, int to, int cap) : from(from), to(to), cap(cap), flow(0), reverse(nullptr) {}
};

vector<vector<Edge*>> adj;
vector<bool> visited;
int source, sink;
void add_edge(int from, int to, int cap){
    Edge* e = new Edge(from,to,cap);
    Edge* e_reverse = new Edge(to,from,0);
    e->reverse=e_reverse;
    e_reverse->reverse=e;
    adj[from].push_back(e);
    adj[to].push_back(e_reverse);
}

int dfs(int cx, int mf){
    if(cx==sink)return mf;
    if(visited[cx])return 0;
    visited[cx]=1;
    for(Edge* e : adj[cx]){
        if(e->cap-e->flow>0){
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
    while(true){
        int flow=dfs(source,INT_MAX);
        fill(visited.begin(),visited.end(),false);
        if(flow==0)break;
        ret+=flow;
        
    }
    return ret;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, M;

    cin >> N >> M;
    adj=vector<vector<Edge*>>(203);
    visited=vector<bool>(203,0);
    source = 0, sink = N + M + 2;
    vector<int> A(N + 1), B(M + 1);

    for (int i = 1; i <= N; i++)
    {
        cin >> A[i];
    }
    for (int i = 1; i <= M; i++)
    {
        cin >> B[i];
    }
    for (int i = 1; i <= M; i++)
    {
        add_edge(source, i, B[i]);
        for (int j = 1; j <= N; j++)
        {
            int a;
            cin >> a;
            if(a==0)continue;
            add_edge(i, j + M, a);
        }
    }

    for (int i = 1; i <= N; i++)
    {
        add_edge(i + M, sink, A[i]);
    }
    cout << max_flow();
}