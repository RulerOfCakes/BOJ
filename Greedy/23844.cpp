#include <bits/stdc++.h>
using namespace std;
int N,K;
int level[10101];
int lvls[10101];
vector<int> adj[10101];
void dfs(int x=1,int prt=0){
    level[x]=level[prt]+1;
    lvls[level[x]]++;
    for(int nx:adj[x]){
        if(nx==prt)continue;
        dfs(nx,x);
    }
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>N>>K;
    for(int i = 1; i <= N-1; i++){
        int a,b;cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs();
    int ans=0;
    for(int i = 1; i <= N; i++){
        if(lvls[i]>K)ans+=lvls[i]-K;
    }
    cout << N-ans;
}