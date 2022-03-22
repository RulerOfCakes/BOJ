#include <bits/stdc++.h>
using namespace std;
int N;
int pref[502][502];
int visited[502][502];
vector<vector<int>> adj(502);
void dfs(int ori, int cx){
    if(visited[ori][cx])return;
    visited[ori][cx]=1;
    for(int nx:adj[cx]){
        dfs(ori,nx);
    }
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>N;
    for(int i = 1; i <= N; i++){
        bool found=0;
        for(int j = 1; j <= N; j++){
            cin>>pref[i][j];
            if(pref[i][j]==i)found=1;
            if(!found)adj[i].push_back(pref[i][j]);
        }
    }
    for(int i = 1; i <= N; i++){
        dfs(i,i);
    }
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            if(pref[i][j]==i){
                cout << i << '\n';
                break;
            }
            int cx=pref[i][j];
            if(visited[i][cx]&&visited[cx][i]){cout<<cx<<'\n';break;}
        }
    }
}