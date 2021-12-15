#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi=pair<int,int>;
const int INF = 1e9+7;
int N,M;
vector<vector<pi>> adj,madj;

int prim(int sx){
    vector<bool> visited(N+1,0);
    vector<int> enlist(N+1,INF);
    vector<int> pred(N+1,0);
    priority_queue<pi> pq;
    pq.push({0,sx});
    int ret=0;
    while(!pq.empty()){
        int cx,cc;
        tie(cc,cx)=pq.top();
        pq.pop();
        if(visited[cx]||enlist[cx]<cc)continue;
        cc=-cc;
        if(pred[cx]){
            madj[pred[cx]].push_back({cx,cc});
            madj[cx].push_back({pred[cx],cc});
        }
        visited[cx]=1;
        ret+=cc;
        for(auto [nx,nc]:adj[cx]){
            if(visited[nx]||enlist[nx]<=nc)continue;
            enlist[nx]=nc;
            pred[nx]=cx;
            pq.push({-nc,nx});
        }
    }
    return ret;
}

int ans;
void dfs(int x, int t, int cc, int prt){
    if(ans)return;
    if(x==t){
        ans=cc;
        return;
    }
    for(auto [nx,nc]:madj[x]){
        if(nx==prt)continue;
        dfs(nx,t,max(cc,nc),x);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M;
    adj.resize(N+1);
    madj.resize(N+1);

    for(int i = 0; i < M; i++){
        int a,b,c;
        cin>>a>>b>>c;
        adj[a].push_back({b,c});
        adj[b].push_back({a,c});
    }
    int tt=prim(1);
    int Q;
    cin>>Q;
    while(Q--){
        int a,b;cin>>a>>b;
        ans=0;
        dfs(a,b,0,0);
        cout << tt-ans << '\n';
    }
}