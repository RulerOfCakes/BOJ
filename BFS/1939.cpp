#include <bits/stdc++.h>
using namespace std;
using pi=pair<int,int>;
int N,M,A,B,ans;
vector<vector<pi>>adj;
bool visited[101010];
int bfs(int sx, int val){
    queue<pi> q;
    q.push({sx,val});
    visited[sx]=1;
    int ret=-1;
    while(!q.empty()){
        int cx,cm;
        tie(cx,cm)=q.front();
        q.pop();
        //if(visited[cx])continue;
        if(cx==B){
            if(ret==-1)ret=cm;
            else
                ret=min(ret,cm);
            continue;
        }
        for(auto [nx,nm]:adj[cx]){
            if(visited[nx]||cm>nm)continue;
            visited[nx]=1;
            q.push({nx,cm});
        }
    }
    return ret;
}
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> N >> M;

    adj.resize(N+2);
    int mxv=0;
    for(int i = 0; i < M; i++){
        int a,b,c;
        cin>>a>>b>>c;
        adj[a].push_back({b,c});
        adj[b].push_back({a,c});
        mxv=max(mxv,c);
    }
    cin>>A>>B;
    int l=0,r=mxv,ans=0;
    while(l<=r){
        int md=l+r>>1;
        memset(visited,0,sizeof(visited));
        if(bfs(A,md)==-1){
            r=md-1;
        }
        else{
            ans=max(ans,md);
            l=md+1;
        }
    }
    cout << ans;
}