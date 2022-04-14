#include <bits/stdc++.h>
using namespace std;
using pi = pair<int,int>;
int N;
int dist[50505];
int boo,boodist;
vector<pi>adj[50505];

void rdfs(int cx, int prt, int cc){
    dist[cx]=max(dist[cx],cc);
    if(dist[cx]>boodist)boodist=dist[cx],boo=cx;
    for(pi np:adj[cx]){
        if(np.first==prt)continue;
        rdfs(np.first,cx,cc+np.second);
    }
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>N;
    for(int i = 1; i < N; i++){
        int a,b,c;
        cin>>a>>b>>c;
        adj[a].push_back({b,c});
        adj[b].push_back({a,c});
    }
    rdfs(1,0,0);
    rdfs(boo,0,0);
    rdfs(boo,0,0);
    for(int i = 1; i <= N; i++){
        cout << dist[i] << '\n';
    }
}