#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi=pair<int,int>;
using pl=pair<ll,ll>;
int N,M;
vector<vector<pl>> adj,madj;
vector<pi> attr;

ll cost(int i, int j){
    return (attr[i].second+attr[j].second)/abs(attr[i].first-attr[j].first);
}

ll prim(int sx){
    vector<int> pred(N+1,0);
    vector<bool> vstd(N+1);
    vector<ll> enlist(N+1,-1e18);
    priority_queue<pl> pq;
    pq.push({0,sx});
    enlist[sx]=0;
    ll ret=0;
    while(!pq.empty()){
        ll cx,cc;
        tie(cc,cx)=pq.top();
        pq.pop();
        if(vstd[cx]||enlist[cx]>cc)continue;
        vstd[cx]=1;
        if(pred[cx]){
            madj[pred[cx]].push_back({cx,cc});
            madj[cx].push_back({pred[cx],cc});
        }
        ret+=cc;
        for(auto [nx,nc]:adj[cx]){
            if(vstd[nx]||enlist[nx]>=nc)continue;
            enlist[nx]=nc;
            pred[nx]=cx;
            pq.push({nc,nx});
        }
    }
    return ret;
}
vector<bool>visited;
void dfs(int x){
    visited[x]=1;
    for(auto [nx,nc]:madj[x]){
        if(visited[nx])continue;
        dfs(nx);
        cout << x << ' ' << nx << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    adj.resize(N+1);
    madj.resize(N+1);
    visited.resize(N+1);
    for(int i = 0; i < N; i++){
        int a,b;cin>>a>>b;
        attr.push_back({a,b});
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j <N; j++){
            if(i==j)continue;
            adj[i+1].push_back({j+1, cost(i,j)});
        }
    }
    ll ret=prim(1);
    cout << ret << endl;
    dfs(1);
}