#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<int,int>;
using pl = pair<ll,ll>;
//7!=5040
int N, M;
vector<vector<pi>> adj;
vector<vector<ll>> dist;
void dstra(int x, int p){
    priority_queue<pl> pq;
    pq.push({0,x});
    dist[x][p]=0;
    while(!pq.empty()){
        ll cx,cc;
        tie(cc,cx)=pq.top();
        cc=-cc;
        pq.pop();
        if(dist[cx][p]<cc)continue;
        for(auto np : adj[cx]){
            ll nx=np.first,nc=np.second;
            if(dist[nx][p]<=nc+cc)continue;
            dist[nx][p]=nc+cc;
            pq.push({-(nc+cc),nx});
        }
    }
}
vector<int> balllocs;
ll sol(int x, int r, int bt){
    if(bt==(1<<7)-1)return 0;
    ll ret=1e12;
    for(int i = 0; i < 7; i++){
        if(bt&(1<<i))continue;
        int nbt=bt|(1<<i);
        ret=min(ret,sol(balllocs[i],i,nbt)+dist[balllocs[i]][r]);
    }
    return ret;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> N >> M;
    adj.resize(N+1);
    dist.resize(N+1, vector<ll>((9),1e12));
    for(int i=0; i < M; i++){
        int a,b,c;
        cin >> a >> b >> c;
        adj[a].push_back({b,c});
        adj[b].push_back({a,c});
    }
    for(int i = 0; i < 7; i++){
        int db;
        cin >> db;
        balllocs.push_back(db);
        dstra(db,i);
    }
    dstra(1,8);
    ll res=sol(1,8,0);
    if(res==1e12)cout <<-1;
    else cout << res;
}