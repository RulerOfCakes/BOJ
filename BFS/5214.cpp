#include <bits/stdc++.h>
using namespace std;
using pi = pair<int,int>;
int N,K,M;
vector<int> adj[201010];

int bfs(){
    vector<int> dist(N+M+2, -1);
    queue<pi> q;
    dist[1]=1;
    q.push({1,1});
    while(!q.empty()){
        int cx,cc;
        tie(cc,cx)=q.front();
        q.pop();
        for(int nx : adj[cx]){
            if(dist[nx]!=-1)continue;
            dist[nx]=cc+(nx>N?0:1);
            q.push({dist[nx],nx});
        }
    }
    return dist[N];
}
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> N >> K >> M;
    for(int i = 1; i <= M; i++){
        int a;
        for(int j = 0; j < K; j++){
            cin >> a;
            adj[a].push_back(N+i);
            adj[N+i].push_back(a);
        }
    }
    if(N==1)cout << 1;
    else
        cout << bfs();
}