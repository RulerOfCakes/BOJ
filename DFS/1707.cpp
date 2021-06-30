#include <bits/stdc++.h>

using namespace std;

int T, V, E;
vector<vector<int>> v;
vector<vector<int>> visited;

bool dfs(int x, int parity){
    if(visited[x][parity^1])return 0;
    visited[x][parity]=1;
    bool ret = 1;
    for(int i : v[x]){
        if(visited[i][parity^1])continue;
        ret = ret && dfs(i, parity^1);
    }
    return ret;
}

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> T;
    while(T--){
        cin >> V >> E;
        visited = vector<vector<int>>(V+1, vector<int>(2, 0));
        v = vector<vector<int>>(V+1, vector<int>());
        for(int i = 0; i < E; i++){
            int a, b;
            cin >> a >> b;
            v[a].push_back(b);
            v[b].push_back(a);
        }
        bool anscheck = 1;
        for(int i = 1; i <= V; i++){
            if(!visited[i][0]&&!visited[i][1]){
                if(!dfs(i, 0)){
                    anscheck = 0;
                    break;
                }
            }
        }
        if(anscheck){
            cout << "YES\n";
        }
        else cout << "NO\n";
    }
}