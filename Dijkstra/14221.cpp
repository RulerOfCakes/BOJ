#include <bits/stdc++.h>
using namespace std;
using pi = pair<int,int>;
const int INF=1e9+7;
int dist[5202];
vector<pi> adj[5202];
vector<int> pv;
map<int,int> mp;
int V,E,P,Q;
int dstra(){
   priority_queue<pair<pi,int>, vector<pair<pi,int>>,greater<pair<pi,int>>> pq;
   for(auto cx:pv){
       pq.push({{0,cx},cx});
   }
   while(!pq.empty()){
      int cc=pq.top().first.first,cx=pq.top().second,ox=pq.top().first.second;
      pq.pop();
      if(dist[cx]<cc)continue;
      if(mp.find(cx)!=mp.end()){
          return ox;
      }
      for(auto e : adj[cx]){
         int nx=e.first,nc=e.second;
         if(dist[nx]<=cc+nc)continue;
         dist[nx]=cc+nc;
         pq.push({{cc+nc,ox},nx});
      }
   }
   assert(false);
   return -1;
}
int main()
{
   cin>>V>>E;
   for(int i = 1; i <= V; i++)dist[i]=INF;
   for(int i = 0; i < E; i++){
      int u,v,w;
      cin >> u >> v >> w;
      adj[u].push_back({v,w});
      adj[v].push_back({u,w});
   }
   cin >> P >> Q;
   for(int i =0; i < P; i++){
       int a;cin>>a;pv.push_back(a);
   }
   for(int i =0; i < Q; i++){
       int a;cin>>a;mp[a]=1;
   }
   cout << dstra();
}
