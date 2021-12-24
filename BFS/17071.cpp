#include <bits/stdc++.h>
using namespace std;
using pi = pair<int,int>;
int N,M;
int vis[505050][2];
void bfs(int x){
    queue<pi> q;
    q.push({x,0});
    while(!q.empty()){
        int cx,cc;
        tie(cx,cc)=q.front();
        q.pop();
        if(vis[cx][cc%2]!=-1)continue;
        vis[cx][cc%2]=cc;
        for(int nx:{cx-1,cx+1,cx*2}){
            if(nx<0||nx>500000)continue;
            if(vis[nx][(cc+1)%2]!=-1)continue;
            q.push({nx,cc+1});
        }
    }
}
void sol(int x){
    for(int i = 0; i <=500000; i++){
        int inc=i*(i+1)/2,nx=x+inc;
        if(nx>500000)break;
        if(vis[nx][i%2]!=-1&&vis[nx][i%2]<=i){
            cout << i;
            return;
        }
    }
    cout << -1;
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>N>>M;
    memset(vis,-1,sizeof(vis));
    bfs(N);
    sol(M);
}