#include <bits/stdc++.h>

using namespace std;
int N, M;
vector<vector<int>> v;
int visited[1002];

void bfs(int x){
    queue<int> q;
    q.push(x);
    visited[x] = 1;
    while(!q.empty()){
        int cur = q.front();
        q.pop();

        for(auto a : v[cur]){
            if(!visited[a]){
                visited[a] = 1;
                q.push(a);
            }
        }
    }
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M;
    v = vector<vector<int>>(N+1, vector<int>());
    for(int i = 0; i < M; i++){
        int a, b;
        cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    int ans = 0;
    for(int i = 1; i <= N; i++){
        if(!visited[i]){
            bfs(i);
            ans++;
        }
    }
    cout << ans;
    
}