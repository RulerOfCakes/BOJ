#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int, int>;
using pl = pair<ll, int>;

const int MAX = 10002;
int V, E, S, T;
int id;           // unique node id
int visited[MAX]; // visit/parent

bool finished[MAX];      // dfs completion check
vector<vector<int>> a;   // nodes
vector<vector<int>> SCC; // scc

vector<int> sccidx;

stack<int> s;

int dfs(int x)
{
    visited[x] = ++id;
    s.push(x);

    int parent = visited[x];

    for (int i = 0; i < a[x].size(); i++)
    {
        int y = a[x][i];

        if (visited[y] == 0)
        {
            parent = min(parent, dfs(y));
        }
        else if (!finished[y])
        {
            parent = min(parent, visited[y]);
        }
    }

    // scc found
    if (parent == visited[x])
    {
        vector<int> scc;

        while (1)
        {
            int t = s.top();
            s.pop();
            scc.push_back(t);
            sccidx[t] = SCC.size();
            finished[t] = true;
            if (t == x)
                break;
        }

        //sort(scc.begin(),scc.end());
        SCC.push_back(scc);
    }

    return parent;
}

int sol(vector<vector<int>>& v){
    priority_queue<pi> pq;
    pq.push({SCC[sccidx[S]].size(), sccidx[S]});
    vector<int> tvisited(v.size()+2, 0);
    int ret=0;
    
    while(!pq.empty()){
        int cx, cc;
        tie(cc, cx) = pq.top();
        pq.pop();
        if(tvisited[cx]>=cc)continue;
        tvisited[cx]=cc;
        if(cx==sccidx[T]){
            ret=max(cc,ret);
        }
        for(int nx : v[cx]){
            if(tvisited[nx]>=cc+SCC[nx].size())continue;
            pq.push({cc+SCC[nx].size(), nx});
        }
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    

    cin >> V >> E >> S >> T;
    a = vector<vector<int>>(MAX, vector<int>());
    SCC = vector<vector<int>>();
    sccidx = vector<int>(MAX, 0);
    

    for (int i = 0; i < E; i++)
    {
        int at, bt;
        cin >> at >> bt;
        a[at].push_back(bt);
    }

    for (int i = 1; i <= V; i++)
    {
        if (!visited[i])
            dfs(i);
    }

    vector<vector<int>> sccedges(SCC.size()+2, vector<int>());
    for(int i = 0; i < SCC.size(); i++){
        for(int cx : SCC[i]){
            for(int nx: a[cx]){
                if(sccidx[nx]==i)continue;
                sccedges[i].push_back(sccidx[nx]);
            }
        }
    }
    cout << sol(sccedges);
}