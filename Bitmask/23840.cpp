#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<int,int>;
using pl = pair<ll,ll>;
//const int INF = 1e9;
const ll LNF = 1e16;
int T,N,M,X,Z,P;

vector<vector<pi>> adj;
vector<int> midp;
vector<vector<ll>>dist;
//vector<vector<ll>>dp(21,vector<ll>(1<<20,LNF));
//TIL: vector constructors take a long ass time
ll dp[21][1<<20];
void dijkstra(int s, int p){
    priority_queue<pl> pq;
    pq.push({0,s});
    dist[p][s]=0;
    while(!pq.empty()){
        ll cx,cc;
        tie(cc,cx)=pq.top();
        cc=-cc;
        pq.pop();
        if(dist[p][cx]<cc)continue;
        for(auto np : adj[cx]){
            ll nx,nc;
            tie(nx,nc)=np;
            if(dist[p][nx]<=cc+nc)continue;
            dist[p][nx]=cc+nc;
            pq.push({-(cc+nc),nx});
        }
    }
}
bool found=0;

ll sol(int ci, int bt){
    if(bt==(1<<P)-1){
        found=1;
        return dist[ci][Z];
    }
    ll& ret=dp[ci][bt];
    if(ret!=-1)return ret;
    ret=LNF;
    for(int i = 0; i < P; i++){
        if(bt&(1<<i)||dist[ci][midp[i]]==LNF)continue;
        int nbt=bt|(1<<i);
        ret=min(ret,sol(i,nbt)+dist[ci][midp[i]]);
    }
    return ret;
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
        
    cin >> N >> M;
    adj=vector<vector<pi>>(N+1,vector<pi>());
    memset(dp,-1,sizeof(dp));
    for(int i = 0; i < M; i++){
        int a,b,c;
        cin >> a >> b >> c;
        adj[a].push_back({b,c});
        adj[b].push_back({a,c});
    }

    cin>> X >> Z >> P;
    dist=vector<vector<ll>>(P+1,vector<ll>(N+1,LNF));
    
    for(int i=0;i<P;i++){
        int a;cin>>a;midp.push_back(a);
        dijkstra(a,i);
    }
    midp.push_back(X);
    dijkstra(X,P);
    ll ans = sol(P,0);
    if(ans>=LNF||!found)cout << -1;
    else cout << ans;
}