#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int, int>;
using pl = pair<ll, int>;

const int MAX = 10002;
int V, E;
int id; // unique node id
int visited[MAX]; // visit/parent

bool finished[MAX]; // dfs completion check
vector <int> a[MAX]; // nodes
vector <vector <int> > SCC; // scc

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
        sort(scc.begin(),scc.end());
        SCC.push_back(scc);
    }

    return parent;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> V >> E;
    for(int i = 0; i < E; i++){
        int at, bt;
        cin >> at >> bt;
        a[at].push_back(bt);
    }
    for(int i = 1; i <= V; i++){
        if(!visited[i])dfs(i);
    }
    cout << SCC.size() << '\n';
    
    sort(SCC.begin(),SCC.end(), [&](vector<int>& a, vector<int>& b){
        return a[0]<b[0];
    });
    for(int i = 0; i < SCC.size(); i++){
        
        for(int j = 0; j < SCC[i].size(); j++){
            cout << SCC[i][j] << ' ';
        }
        cout << -1 << '\n';
    }
}