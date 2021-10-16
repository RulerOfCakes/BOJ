#include <bits/stdc++.h>

using namespace std;
using pi = pair<int,int>;


int M, N, Q;
vector<vector<int>> adj;
int dist[1010],ans[202020];
void bfs(int sx){
    queue<int>q;
    q.push(sx);
    while(!q.empty()){
        int cx = q.front();
        q.pop();
        for(auto i : adj[cx]){
            //cout << i << ' ' << dist[i] << endl;
            if(dist[i]>dist[cx]+1){
                dist[i]=dist[cx]+1;
                
                q.push(i);
            }
        }
    }
}
int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M >> Q;
    vector<pi> edges,qry;
    adj=vector<vector<int>>(N+1,vector<int>());
    vector<bool> checkout(M+1);
    
    edges.push_back({0,0});
    for (int i = 0; i < M; i++)
    {
        int a,b;
        cin >> a >> b;
        edges.push_back({a,b});
    }
    for(int i = 0; i < Q; i++){
        char c;
        int a;
        cin >> c >> a;
        qry.push_back({(c=='U'?1:2),a});
        if(c=='U')checkout[a]=1;
    }
    
    reverse(qry.begin(),qry.end());
    for(int i = 1; i <= M; i++){
        if(!checkout[i]){
            int s = edges[i].first,e=edges[i].second;
            adj[s].push_back(e);
        }
    }
    fill(dist,dist+N+1,1e9);
    dist[1]=0;
    bfs(1);
    int qcount=0;
    
    for(auto p : qry){
        if(p.first==1){
            //new edge
            int s = edges[p.second].first,e=edges[p.second].second;
            adj[s].push_back(e);
            bfs(s);
        }
        else{
            ans[qcount++]=dist[p.second]>1e8?-1:dist[p.second];
        }
    }
    for(int i = qcount-1; i >= 0; i--){
        cout << ans[i] << '\n';
    }
}