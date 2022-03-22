#include <bits/stdc++.h>
using namespace std;
using pi = pair<int,int>;
using ti = tuple<int,int,int>;
int N,M,K;
vector<pi> adj[1010];
vector<vector<int>> ballv(1010);

int dstra(const vector<vector<int>>& nballv){
    priority_queue<ti,vector<ti>,greater<ti>> pq;
    pq.push({0,0,1});
    vector<vector<int>> visited(N+1,vector<int>(1<<7,INT_MAX));
    visited[1][0]=0;
    while(!pq.empty()){
        auto [cc,cb,cx] = pq.top();
        pq.pop();
        if(visited[cx][cb]<cc)continue;

        for(auto bt : nballv[cx])cb|=(1<<bt);
        if(cb==(1<<7)-1)return cc;

        for(auto [nx,nc]:adj[cx]){
            if(visited[nx][cb]<=cc+nc)continue;
            visited[nx][cb]=cc+nc;
            pq.push({cc+nc,cb,nx});
        }
    }
    return -1;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>N>>M>>K;
    for(int i = 0; i < M; i++){
        int a,b,c;cin>>a>>b>>c;
        adj[a].push_back({b,c});
        adj[b].push_back({a,c});
    }
    for(int i = 0; i < K; i++){
        int c,d;
        cin>>c>>d;
        ballv[c].push_back(d);
    }
    // 7!/7^7 = 0.006, therefore 1000 runs should be safe to ensure at least 1 permutation roll
    // odds of unsafety : P(x>=1000) = 0.00243 (geometric distribution, p = 0.006)
    int run = 1000,ans=INT_MAX;
    while(run--){
        random_device rd;
        mt19937 rng(rd());
        uniform_int_distribution<int> fix(0,6);
        auto gen = bind(fix,rng);
        vector<int> newballs(N+1);
        for(int i = 1; i <= N; i++){
            newballs[i]=gen();
        }
        vector<vector<int>> nballv(1010);
        for(int i = 1; i <= N; i++){
            for(auto ball : ballv[i]){
                nballv[i].push_back(newballs[ball]);
            }
        }
        int ret = dstra(nballv);
        if(ret!=-1){
            ans=min(ans,ret);
        }
    }
    cout << (ans!=INT_MAX?ans:-1);
}