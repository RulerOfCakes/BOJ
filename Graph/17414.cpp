#include <bits/stdc++.h>

using namespace std;
using pi = pair<int,int>;
int V, E;
stack<pi> s[200002];
vector<int> visited;
vector<int> nvisited;

//int pos[1002];//current check position in dfs
int parent[200002];

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
int check(int start){
    int odd=s[start].size()%2;
    
    while(!s[start].empty()){
        int nxt, nxtid;
        tie(nxt,nxtid)=s[start].top();
        s[start].pop();
        if(visited[nxtid])continue;
        visited[nxtid]=1;
        odd+=check(nxt);
    }
    return odd;
    
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> V >> E;
    for(int i = 0; i <= V; i++){
        parent[i] = i;
    }
    for(int i = 0; i < E; i++){
        int a, b;
        cin >> a >> b;
        uni(a,b);
        s[a].push({b,i});
        s[b].push({a,i});
    }
    visited=vector<int>(E+1,0);
    nvisited=vector<int>(V+1,0);

    vector<int> groups;
    for(int i = 1; i <= V; i++){
        if(!nvisited[i]){
            groups.push_back(check(i));
        }
    }
    // for(int i = 1; i <= N; i++)pos[i]=1;
    // dfs(1);
}