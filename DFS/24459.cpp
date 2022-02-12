#include <bits/stdc++.h>
using namespace std;
using pi = pair<int,int>;
vector<pi> adj[101010];
vector<int> rts;
int N;

//parity -> min, !parity -> max
pi dfs(int x, int prt, bool parity){
    int ret=(parity?1e9:0),ans=x;
    for(auto [nx,nw]:adj[x]){
        if(nx==prt)continue;
        pi tret=dfs(nx,x,parity);
        int res=tret.first+nw;
        ret=(parity?min(res,ret):max(res,ret));
        if(ret==res)ans=tret.second;
    }
    if(ret==1e9&&parity)ret=0;
    return {ret,ans};
}
int bfs(){
    priority_queue<pi> pq;
    vector<pi> vs(N,{-1,-1});
    for(auto cx:rts){
        pq.push({0,cx});
        vs[cx]={cx,0};
    }
    int ret=1e9;
    while(!pq.empty()){
        auto [cc,cx]=pq.top();
        cc=-cc;
        pq.pop();


        for(auto [nx,nc]:adj[cx]){
            if(vs[nx].first==vs[cx].first)continue;
            else if(vs[nx].first!=vs[cx].first&&vs[nx].first!=-1){
                //found
                ret=min(ret,nc+cc+vs[nx].second);
                if(vs[nx].second>cc+nc){
                    vs[nx]={vs[cx].first,nc+cc};
                    pq.push({-(nc+cc),nx});
                }
            }
            else{
                pq.push({-(nc+cc),nx});
                vs[nx]={vs[cx].first,nc+cc};
            }
        }
    }
    return ret;
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>N;
    for(int i = 1; i < N; i++){
        int p,q,w;
        cin>>p>>q>>w;
        adj[p].push_back({q,w});
        adj[q].push_back({p,w});
    }
    for(int i = 0; i < N; i++)if(adj[i].size()==1)rts.push_back(i);
    pi d1=dfs(rts.front(),-1,0);
    pi d2=dfs(d1.second,-1,0);
    cout << max(d1.first,d2.first) << '\n';
    cout << bfs();
}