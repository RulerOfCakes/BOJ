#include <bits/stdc++.h>

using namespace std;

int N, M;
const int INF = 1e6;
vector<int> visited;
vector<int> match1, match2;
vector<vector<int>> v;
int vcnt;

bool dfs(int x){
    if(visited[x]==vcnt)return false;
    visited[x]=vcnt;

    for(int i = 0; i < v[x].size(); i++){
        int next = v[x][i];
        if(!match2[next] || dfs(match2[next])){
                match1[x]=next;
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
    cin >> N;
    v = vector<vector<int>>(INF+1, vector<int>());
    visited = vector<int>(INF+1 , 0);
    match1 = vector<int>(INF+1, 0);
    match2 = vector<int>(INF+1, 0);
    for(int i = 1; i <= N; i++){
        int a, b;
        cin >> a >> b;
        v[i].push_back(a);
        v[i].push_back(b);
    }
    int ans=0;
    vcnt = 1;
    for(int i = 1; i <= N; i++){
        
        vcnt++;
        if(dfs(i))ans++;
    }
    if(ans<N){
        cout << -1;
    }
    else{
        for(int i = 1; i <= N; i++){
            cout << match1[i] << '\n';
        }
    }
}