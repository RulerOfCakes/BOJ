#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<int,int>;
const int INF = 1e9;
int T,N,M;

vector<vector<pi>> adj;
vector<int> dist;


void dijkstra(int s){
    priority_queue<pi> pq;
    pq.push({0,s});
    while(!pq.empty()){
        int cx,cc;
        tie(cc,cx)=pq.top();
        cc=-cc;
        pq.pop();
        if(dist[cx]<cc)continue;
        for(auto np : adj[cx]){
            int nx,nc;
            tie(nx,nc)=np;
            if(dist[nx]<=cc+nc)continue;
            dist[nx]=cc+nc;
            pq.push({-(cc+nc),nx});
        }
    }
}


int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
        
    cin >> N >> M;
    adj=vector<vector<pi>>(N+1,vector<pi>());
    for(int i = 0; i < M; i++){
        int a,b,c;
        cin >> a >> b >> c;
        adj[a].push_back({b,c});
    }
    int ans = INF;
    dist=vector<int>(N+1,INF);
    for(int i = 1; i <= N; i++){
        dist=vector<int>(N+1,INF);
        dijkstra(i);
        ans=min(ans,dist[i]);
    }
    if(ans==INF){
        cout << -1;
    }
    else
        cout << ans;
}