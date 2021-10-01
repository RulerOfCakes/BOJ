#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int, int>;
using pl = pair<ll, int>;

class edge
{
public:
    int u, v;
    ll w;
    edge(int a, int b, ll c)
    {
        u = a;
        v = b;
        w = c;
    }
    bool operator<(const edge &e) const
    {
        return w < e.w;
    }
    bool operator>(const edge &e) const
    {
        return w > e.w;
    }
};

int N, M, K;

int parent[1002];

int find(int node)
{
    if (node == parent[node])
    {
        return node;
    }
    return parent[node] = find(parent[node]);
}

void uni(int a, int b)
{
    int ar = find(a), br = find(b);

    parent[br] = ar;
}

ll dijkstra(vector<vector<pi>>& edges, int goal){
    vector<int> visited(N+1, 0);
    priority_queue<pl> pq;
    pq.push({0,1});
    while(!pq.empty()){
        int curp; ll curw;
        tie(curw, curp)=pq.top();
        curw=-curw;
        pq.pop();
        if(visited[curp])continue;
        if(curp==goal){
            return curw;
        }
        visited[curp]=1;
        for(auto e : edges[curp]){
            ll nw = e.first; int np = e.second;
            if(visited[np])continue;
            pq.push({-(curw+nw), np});
        }
    }
    return -1;
}


ll dijkstrat(vector<vector<pi>>& edges){
    vector<int> visited(N+1, 0);
    priority_queue<pl> pq;
    priority_queue<pair<int, edge>> eq;
    pq.push({0,1});
    eq.push({0,edge(0,0,0)});
    ll ret = 0;
    while(!pq.empty()){
        int curp; ll curw;
        tie(curw, curp)=pq.top();
        curw=-curw;
        pq.pop();
        edge cur = eq.top().second;
        eq.pop();
        if(visited[curp])continue;
        ret+=cur.w;
        visited[curp]=1;
        for(auto e : edges[curp]){
            ll nw = e.first; int np = e.second;
            if(visited[np])continue;
            pq.push({-(curw+nw), np});
            eq.push({-(curw+nw), edge(curp,np,nw)});
        }
        
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M;
    
    priority_queue<edge, vector<edge>, greater<edge>> ev;
    vector<vector<pi>> edges(N+1, vector<pi>());

    for (int i = 0; i <= N + 1; i++)
    {
        parent[i] = i;
    }
    for (int i = 1; i <= M; i++)
    {
        int u,v,t;
        cin >> u >> v >> t;
        ev.push(edge(u,v,t));
        edges[u].push_back({t,v});
        edges[v].push_back({t,u});
    }
    ll ans = 0;
    cout << dijkstrat(edges);
    // int linecnt1 = 0;
    
    // bool notree=1;
    // int tans=0;
    // while (!ev.empty())
    // {
    //     int x, y;
    //     int weight;
    //     edge te = ev.top();
    //     x = te.u;
    //     y = te.v;
    //     weight = te.w;
    //     ev.pop();
    //     //cout << x  << ' ' << y  << ' ' << weight << endl;
    //     if (find(x) != find(y))
    //     {
    //         edges[x].push_back({weight,y});
    //         edges[y].push_back({weight,x});
    //         linecnt1++;
    //         uni(x, y);
    //         tans+=weight;
    //         if (linecnt1 == N - 1)
    //             break;
    //         if (linecnt1 > N - 1)
    //             notree = 1;
    //     }
    // }
    // cout << tans << "tempans\n";
    // for(int i = 2; i <= N; i++){
    //     ans += dijkstra(edges, i);
    // }
    
}