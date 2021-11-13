#include <bits/stdc++.h>
using namespace std;
using pi = pair<int,int>;
using pp = pair<pi,pi>;
int N;
vector<vector<pi>> adj1,adj2;
int dist[22];
int diff[22];
void dstra(){
    priority_queue<pp> pq;
    //cost, cx, w1, w2
    pq.push({{0,0},{0,0}});
    dist[0]=0;
    while(!pq.empty()){
        int cc=-pq.top().first.first,cx=pq.top().first.second,cw1=pq.top().second.first,cw2=pq.top().second.second;
        pq.pop();
        if(dist[cx]<cc&&diff[cx]<abs(cw1-cw2))continue;
        for(int i = 0; i < adj1[cx].size(); i++){
            int nx = adj1[cx][i].first,nc1=adj1[cx][i].second;
            int nc2 = adj2[cx][i].second;
            int ns1=cw1+nc1,ns2=cw2+nc2;
            if(dist[nx]<=ns1*ns2&&diff[nx]<=abs(ns1-ns2))continue;
            dist[nx]=min(dist[nx],ns1*ns2);
            diff[nx]=min(diff[nx],abs(ns1-ns2));
            pq.push({{-dist[nx],nx},{ns1,ns2}});
        }
    }
}
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> N;
    adj1.resize(N+1);adj2.resize(N+1);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            char c;
            cin >> c;
            if(c=='.')continue;
            int nc=c-'0';
            adj1[i].push_back({j,nc});
        }
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            char c;
            cin >> c;
            if(c=='.')continue;
            int nc=c-'0';
            adj2[i].push_back({j,nc});
        }
    }
    //memset(dist,1e9,sizeof(dist));
    fill(dist,dist+N+1,1e9);
    fill(diff,diff+N+1,1e9);
    dstra();
    if(dist[1]==1e9)cout << -1;
    else cout << dist[1];
}