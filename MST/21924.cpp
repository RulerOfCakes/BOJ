#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi=pair<int,int>;
int N,M;
vector<vector<pi>> adj;

ll prim(int sx){
    vector<bool> visited(N+1,0);
    priority_queue<pi> pq;
    pq.push({0,sx});
    ll ret=0;
    while(!pq.empty()){
        int cx,cc;
        tie(cc,cx)=pq.top();
        pq.pop();
        if(visited[cx])continue;
        visited[cx]=1;
        cc=-cc;
        ret+=cc;
        for(auto [nx,nc]:adj[cx]){
            if(visited[nx])continue;
            pq.push({-nc,nx});
        }
    }
    for(int i = 1; i <= N; i++){
        if(!visited[i])return -1;
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M;
    adj.resize(N+1);
    ll tt=0;
    for(int i = 0; i < M; i++){
        int a,b,c;
        cin>>a>>b>>c;
        tt+=c;
        adj[a].push_back({b,c});
        adj[b].push_back({a,c});
    }
    ll ret=prim(1);
    if(ret==-1)cout << -1;
    else cout << tt-ret;
}