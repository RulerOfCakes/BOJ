#include <bits/stdc++.h>

using namespace std;
using pi = pair<int,int>;
using ll = long long;
int N,P;
int ncost[10101];
vector<pi> adj[101010];

int prim(int sx){
    vector<bool> vstd(N+1);
    priority_queue<pi,vector<pi>,greater<pi>> pq;
    pq.push({ncost[sx],sx});
    int ret=0;
    while(!pq.empty()){
        int cx,cc;
        tie(cc,cx)=pq.top();
        pq.pop();
        if(vstd[cx])continue;
        vstd[cx]=1;
        ret+=cc;
        for(auto [nx,nc]:adj[cx]){
            if(vstd[nx])continue;
            pq.push({nc,nx});
        }
    }
    return ret;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>N>>P;
    int start=0;
    ncost[0]=1e9;
    for(int i = 0; i < N; i++){
        cin>>ncost[i+1];
        if(ncost[i+1]<ncost[start]){
            start=i+1;
        }
    }
    for(int i = 0; i < P; i++){
        int s,e,l;
        cin>>s>>e>>l;
        adj[s].push_back({e,l*2+ncost[s]+ncost[e]});
        adj[e].push_back({s,l*2+ncost[s]+ncost[e]});
    }
    cout << prim(start);
}