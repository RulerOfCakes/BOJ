#include <bits/stdc++.h>
using namespace std;
int N;
vector<int> adj[202020];
int c[202020];
int dfs(int x, int prt){
    int ret=(c[x]==c[prt]?0:1);
    for(int nx : adj[x]){
        if(nx==prt)continue;
        ret+=dfs(nx,x);
    }
    return ret;
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>N;
    for(int i = 0; i < N; i++){
        cin>>c[i+1];
    }
    for(int i = 0; i < N-1; i++){
        int a,b;
        cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    cout << dfs(1,0);
}