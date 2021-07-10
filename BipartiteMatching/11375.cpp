#include <bits/stdc++.h>

using namespace std;

using Edge = tuple<int, int, int>;
using pi = pair<int, int>;

int M, N;
const int INF = 1e9;
vector<bool> visited;
vector<int> match2;
vector<vector<int>> v;

bool dfs(int x){
    if(visited[x])return false;
    visited[x]=1;

    for(int i = 1; i <= M; i++){
        if(v[x][i]){
            if(!match2[i] || dfs(match2[i])){
                //match1[x]=i;
                match2[i]=x;
                return true;
            }
        }
    }
    return false; 
}

int main(){
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M;
    v = vector<vector<int>>(N+1, vector<int>(M+1, 0));
    visited = vector<bool>(N+1 , 0);
    //match1 = vector<int>(N+1, 0);
    match2 = vector<int>(M+1, 0);
    for(int i = 1; i <= N; i++){
        int ta;
        cin >> ta;
        for(int j = 0; j < ta; j++){
            int a;
            cin >> a;
            
            v[i][a]=1;
        }
    }
    int ans=0;

    for(int i = 1; i <= N; i++){
        visited = vector<bool>(N+1, 0);

        if(dfs(i))ans++;
    }
    cout << ans;
}