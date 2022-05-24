#include <bits/stdc++.h>
using namespace std;
int N,M;
vector<int> adj[2020],nadj[2020];
int match2[2020],match1[2020];
vector<int> visited;
bool dfs(int x){
    if(visited[x])return false;
    visited[x]=1;

    for(int i:adj[x]){
        if(!match2[i] || dfs(match2[i])){
            match2[i]=x;
            match1[x]=i;
            return true;
        }
    }
    return false; 
}
int cvisit[2020];
bool cycle(int x, int iter){
    cvisit[x]=iter;
    bool ret = 1;
    for(int nx: nadj[x]){
        if(cvisit[nx]==iter)return false;
        else if(cvisit[nx])continue;
        ret&=cycle(nx,iter);
    }
    return ret;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>N;
    for(int i = 1; i <=N; i++){
        int a;
        cin>>a;
        while(a--){
            int x;cin>>x;
            adj[i].push_back(N+x);
        }
    }

    for(int i = 1; i <= N; i++){
        visited=vector<int>(2020,0);
        if(!dfs(i)){
            cout << -1;
            return 0;
        }
    }
    for(int i = 1; i <= N; i++){
        for(auto nx : adj[i]){
            if(match2[nx]==i){
                nadj[nx].push_back(i);
            } else {
                nadj[i].push_back(nx);
            }
        }
    }
    for(int i = 1; i <= N+N; i++){
        if(!cvisit[i]&&!cycle(i,i)){
            cout << -1;
            return 0;
        }
    }
    cout << 1 << '\n';
    for(int i = 1; i <= N; i++)cout << match1[i]-N << ' ';
}