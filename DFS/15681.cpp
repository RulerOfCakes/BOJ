#include <bits/stdc++.h>
using namespace std;
int N,R,Q;
vector<int> adj[101010];
int l[101010],r[101010];
void dfs(int cx, int prt, int& cnt){
    l[cx]=++cnt;
    for(int nx : adj[cx]){
        if(nx==prt)continue;
        dfs(nx,cx,cnt);
    }
    r[cx]=cnt;
}
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> N >> R >> Q;
    for(int i = 0; i < N-1; i++){
        int u,v;
        cin >>u >>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int cnt=0;
    dfs(R,0,cnt);

    for(int i = 0; i < Q; i++){
        int u;
        cin >> u;
        cout << r[u]-l[u]+1 << '\n';
    }
}