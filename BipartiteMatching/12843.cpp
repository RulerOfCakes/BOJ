#include <bits/stdc++.h>
using namespace std;
int N,M;
vector<int> adj[2020];
int match2[2020];
vector<int> visited;
bool dfs(int x){
    if(visited[x])return false;
    visited[x]=1;

    for(int i:adj[x]){
        if(!match2[i] || dfs(match2[i])){
            match2[i]=x;
            return true;
        }
    }
    return false; 
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>N>>M;
    vector<int> cv;
    for(int i = 0; i <N; i++){
        int a;char c;
        cin>>a>>c;
        if(c=='c'){
            cv.push_back(a);
        }
    }
    for(int i = 0; i < M; i++){
        int a,b;
        cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    int ans = 0;

    for(int x:cv){
        visited=vector<int>(2020);
        if(dfs(x))ans++;
    }

    cout << N-ans;
}