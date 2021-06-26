#include <bits/stdc++.h>

using namespace std;

int N, M;
//const int INF = 1e9;
vector<bool> visited;
vector<int> match2;
vector<vector<int>> v;

bool dfs(int x){
    if(visited[x])return false;
    visited[x]=1;

    for(int i = 0; i < v[x].size(); i++){
        int next = v[x][i];
        if(!match2[next] || dfs(match2[next])){
                //match1[x]=i;
                match2[next]=x;
                return true;
        }
    }
    return false; 
}

int main(){
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M;
    v = vector<vector<int>>(1001, vector<int>());
    visited = vector<bool>(1001 , 0);
    //match1 = vector<int>(N+1, 0);
    match2 = vector<int>(5001, 0);
    for(int i = 1; i <= M; i++){
        int a, b;
        cin >> a >> b;
        v[a].push_back(b);
    }
    int ans=0;

    for(int i = 1; i <= N; i++){
        fill(visited.begin(), visited.end(), 0);

        if(dfs(i))ans++;
    }
    cout << ans;
}