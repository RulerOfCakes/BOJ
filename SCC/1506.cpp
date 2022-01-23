#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int, int>;
using pl = pair<ll, int>;

const int MAX = 102;
int V, E;
int id; // unique node id
int visited[MAX]; // visit/parent

bool finished[MAX]; // dfs completion check
vector <int> a[MAX]; // nodes
vector <vector <int> > SCC; // scc
vector<int> cost(MAX);
stack<int> s;

int dfs(int x) {
    visited[x] = ++id;
    s.push(x);

    int parent = visited[x];

    for(int i=0;i<a[x].size();i++) {
        int y = a[x][i]; 

        if(visited[y]==0) {
            parent = min(parent, dfs(y)); 
        } else if(!finished[y]) { 
            parent = min(parent, visited[y]); 
        }
    }

    // scc found
    if(parent==visited[x]) {
        vector <int> scc;
        while(1) {
            int t = s.top();
            s.pop();
            scc.push_back(t);
            finished[t] = true;
            if(t==x) break;
        }
        sort(scc.begin(),scc.end(),[&](int a, int b){
            return cost[a]<cost[b];
        });
        SCC.push_back(scc);
    }

    return parent;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> V;
    for(int i = 0; i < V; i++){
        cin >> cost[i+1];
    }
    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            char c;cin>>c;
            if(c=='1')a[i+1].push_back(j+1);
        }
    }

    for(int i = 1; i <= V; i++){
        if(!visited[i])dfs(i);
    }
    int ans = 0;
    for(int i = 0; i < SCC.size(); i++){
        ans+=cost[SCC[i].front()];
    }
    cout << ans;
}