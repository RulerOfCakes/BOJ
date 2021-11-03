#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pl = pair<ll, ll>;
using pi = pair<int,int>;
const int INF = 1e9;
vector<vector<pi>> adj;
vector<int> dist;
void dijkstra(int sx){
    priority_queue<pi> pq;
    pq.push({0,sx});
    dist[sx]=0;
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
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int N,M,K;
    cin >> N>>M>>K;
    adj=vector<vector<pi>>(N+1,vector<pi>());
    int s,e;
    for(int i = 0; i < M; i++){
        int a,b;
        cin >> a >> b;
        if(i==K-1){
            adj[a].push_back({b,1});
            adj[b].push_back({a,1});
            s=a,e=b;
        }
        else{
            adj[a].push_back({b,0});
            adj[b].push_back({a,0});
        }
    }
    
    dist=vector<int>(N+1,INF);
    dijkstra(s);
    ll c0=0,c1=0;
    for(int i = 1; i <= N; i++){
        if(dist[i]==1)c1++;
        else c0++;
    }
    // dist=vector<int>(N+1,INF);
    // dijkstra(e);
    // int cc0=0,cc1=0;
    // for(int i = 1; i <= N; i++){
    //     if(dist[i]==1)cc1++;
    //     else cc0++;
    // }
    cout <<c1*c0;
}