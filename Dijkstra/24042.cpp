#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<ll,ll>;

int N,M;
vector<pi> adj[101010];
ll dstra(int sx){
    vector<ll> dist(101010,1e18);
    priority_queue<pi,vector<pi>,greater<pi>> pq;
    pq.push({0,sx});
    dist[sx]=0;
    int ret=-1;
    while(!pq.empty()){
        auto [cc,cx]=pq.top();pq.pop();
        if(dist[cx]<cc)continue;
        if(cx==N)return cc;
        ll cp = cc%M;
        for(auto [nx,nc] : adj[cx]){
            ll np = cp<=nc?nc-cp+1:1+nc+(M-cp);
            if(dist[nx]<=cc+np)continue;
            dist[nx]=cc+np;
            pq.push({cc+np,nx});
        }
    }
    return ret;
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(0);
    cin>>N>>M;
    for(int i =0; i < M; i++){
        int a,b;
        cin>>a>>b;
        adj[a].push_back({b,i});
        adj[b].push_back({a,i});
    }
    cout << dstra(1);
}