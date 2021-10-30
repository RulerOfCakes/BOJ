#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<int,int>;
const int INF = 1e9;
int T,N,M;

vector<vector<pi>> adj;
vector<int> dist;
vector<int> edges;
vector<int> in,out;


void dijkstra(int bit, bool toggle){
    priority_queue<pi> pq;
    for(auto x : edges){
        if((bool)(x&(1<<bit)) == toggle){
            pq.push({-in[x],x});
            dist[x]=in[x];
        }
    }
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
    in=vector<int>(N+1);
    out=vector<int>(N+1);
    for(int i = 0; i < M; i++){
        int a,b,c,d;
        cin >> a >> b >> c >> d;
        if(a!=1&&b!=1){
            adj[a].push_back({b,c});
            adj[b].push_back({a,d});
        } else if (a*b==a){
            edges.push_back(a);
            in[a]=d;
            out[a]=c;
        }
        else if(a*b==b){
            edges.push_back(b);
            in[b]=c;
            out[b]=d;
        }
    }
    int ans=INF;
    //log(5k)=12;
    for(int i = 0; i <= 12; i++){
        dist=vector<int>(N+1,INF);
        dijkstra(i,true);
        for(auto x : edges){
            if(!(x&(1<<i)))ans=min(ans,out[x]+dist[x]);
        }
        dist=vector<int>(N+1,INF);
        dijkstra(i,false);
        for(auto x : edges){
            if(x&(1<<i))ans=min(ans,out[x]+dist[x]);
        }
    }
    cout << ans;
}