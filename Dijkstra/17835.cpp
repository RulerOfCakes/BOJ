#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pl = pair<ll, ll>;
using pi = pair<int, int>;
int N, M, K;
vector<vector<pi>> adj;
vector<int> dest;
vector<ll> dist;
pl dijkstra()
{
    priority_queue<pl> pq;
    dist = vector<ll>(N + 1, 1e18);
    pl ans = {0,0};
    for (int cx : dest)
    {
        pq.push({0, cx});
        dist[cx]=0;
    }
    while(!pq.empty()){
        ll cx,cc;
        tie(cc,cx)=pq.top();
        pq.pop();
        cc=-cc;
        if(dist[cx]<cc)continue;
        if(cc>=ans.first){
            if(cc==ans.first){
                if(cx<ans.second){
                    ans={cc,cx};
                }
            }
            else{
                ans={cc,cx};
            }
        }
        for(auto& [nx,nc] : adj[cx]){
            if(dist[nx]<=cc+nc)continue;
            pq.push({-(cc+nc),nx});
            dist[nx]=cc+nc;
        }
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> N >> M >> K;
    adj = vector<vector<pi>>(N + 1);
    for (int i = 0; i < M; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        adj[b].push_back({a, c});
    }
    for (int i = 0; i < K; i++)
    {
        int a;
        cin >> a;
        dest.push_back(a);
    }
    auto ans = dijkstra();
    cout << ans.second << '\n'
         << ans.first;
}