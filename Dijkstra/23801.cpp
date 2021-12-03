#include <bits/stdc++.h>
using namespace std;
using pi = pair<int,int>;
using ll = long long;
using pl = pair<ll,ll>;
int N,M,X,Z;
vector<vector<pi>> adj;
vector<int> mids;
vector<vector<ll>> dist;

void dstra(int tgl){
    priority_queue<pl> pq;
    if(tgl==0){
        pq.push({0,X});
        dist[X][tgl]=0;
    }
    else if(tgl==1){
        pq.push({0,Z});
        dist[Z][tgl]=0;
    }

    while(!pq.empty()){
        ll cx, cc;
        tie(cc,cx)=pq.top();
        cc=-cc;
        pq.pop();
        if(dist[cx][tgl]<cc)continue;
        for(auto [nx,nc] : adj[cx]){
            if(dist[nx][tgl]<=cc+nc)continue;
            dist[nx][tgl]=cc+nc;
            pq.push({-(cc+nc),nx});
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M;
    adj.resize(N+1);
    dist.resize(N+1,vector<ll>(2,1e18));
    while(M--){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    cin >>X>>Z;
    int P;
    cin >> P;
    while(P--){
        int a;
        cin >> a;
        mids.push_back(a);
    }
    dstra(0);dstra(1);
    ll ans=1e18;
    for(auto p : mids){
        ans=min(ans,dist[p][0]+dist[p][1]);
    }
    if(ans>=1e18){
        cout << -1;
    }
    else
        cout << ans;
}