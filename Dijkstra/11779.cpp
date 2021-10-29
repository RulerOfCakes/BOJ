#include <bits/stdc++.h>
using namespace std;
using pi = pair<int,int>;
vector<vector<pi>>adj,radj;
vector<int> dist;

int s,e;
int dijkstra(){
    dist.resize(adj.size()+1,2e9);
    priority_queue<pi> pq;
    pq.push({0,s});
    while(!pq.empty()){
        int cx,cc;
        tie(cc,cx)=pq.top();
        cc=-cc;
        pq.pop();
        if(dist[cx]<=cc)continue;
        dist[cx]=cc;
        if(cx==e)return cc;
        for(auto np : adj[cx]){
            int nx,nc;
            tie(nx,nc)=np;
            if(dist[nx]<=cc+nc)continue;
            pq.push({-(cc+nc),nx});
        }
    }
    return -1;
}

deque<int> backtrack(){
    deque<int> dq;
    dq.push_back(e);
    while(dq.front()!=s){
        int cx = dq.front();
        for(auto np : radj[cx]){
            int nx,nc;
            tie(nx,nc)=np;
            if(dist[nx]==dist[cx]-nc){
                dq.push_front(nx);
                break;
            }
        }
    }
    return dq;
}
int main(){
    int V,E;
    cin >> V >> E;adj.resize(V+1,vector<pi>());radj.resize(V+1,vector<pi>());
    for(int i = 0; i < E; i++){
        int a,b,c;
        cin >> a >> b >> c;
        adj[a].push_back({b,c});
        radj[b].push_back({a,c});
    }
    
    cin >> s >> e;
    cout << dijkstra() << endl;
    auto dq = backtrack();
    cout << dq.size() << endl;
    for(auto n : dq){
        cout << n << ' ';
    }
}