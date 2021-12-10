#include <bits/stdc++.h>
using namespace std;
int N;
vector<int> adj[1010100];
char pth[1005050];

void dfs(int cx, int prt){
    char c;
    if(pth[prt]=='X')c='Y';
    else c='X';
    pth[cx]=c;
    for(auto nx: adj[cx]){
        if(pth[nx]!='Z')continue;
        dfs(nx,cx);
    }
}
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> N;
    pth[0]='Y';
    for(int i = 1; i <= N; i++){
        int a,b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        adj[2*i-1].push_back(2*i);
        adj[2*i].push_back(2*i-1);
        pth[i]='Z';
    }
    for(int i = N+1; i <= 2*N; i++){
        pth[i]='Z';
    }
    for(int i = 1; i <= 2*N; i++){
        if(pth[i]=='Z')dfs(i,0);
    }
    for(int i = 1; i <= 2*N; i++){
        cout << pth[i];
    }
}