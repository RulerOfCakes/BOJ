#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;

const int MAX_N = 200005;
int sz[MAX_N], ans, N, K;
int visited[MAX_N];
vector<vector<pi>> adj;
map<int, int> mp;

int getSize(int cx, int parent)
{
    sz[cx] = 1;
    for (auto p : adj[cx])
    {
        int nx = p.first;
        if (visited[nx] || nx == parent)
            continue;
        sz[cx] += getSize(nx, cx);
    }
    return sz[cx];
}

int centroid(int cx, int parent, int cap)
{
    for (auto p : adj[cx])
    {
        int nx = p.first;
        if (visited[nx] || nx == parent)
            continue;
        if (sz[nx] > cap)
            return centroid(nx, cx, cap);
    }
    return cx;
}

int roads(int cx, int parent, int dist, int depth){
    int ret=1e9;
    if(dist>K)return ret;
    
    if(mp.find(K-dist)!=mp.end())ret=mp[K-dist]+depth;

    for(auto&&[nx,c] : adj[cx]){
        if(nx==parent||visited[nx])continue;
        ret=min(ret,roads(nx,cx,dist+c,depth+1));
    }
    return ret;
}

void update(int cx, int parent, int dist, int depth){
    if(dist>K)return;
    if(mp.find(dist)!=mp.end())mp[dist]=min(mp[dist],depth);
    else mp[dist]=depth;
    for(auto&&[nx,c] : adj[cx]){
        if(visited[nx]||nx==parent)continue;
        update(nx,cx,dist+c,depth+1);
    }
}

void sol(int cx){
    int cap=getSize(cx,-1)/2;
    int cen=centroid(cx,-1,cap);
    visited[cen]=1;
    mp.clear();
    mp[0]=0;
    for(auto&&[nx,c] : adj[cen]){
        if(!visited[nx]){
            ans=min(ans,roads(nx,cen,c,1));
            update(nx,cen,c,1);
        }
    }
    for(auto&&[nx, c] : adj[cen]){
        if(!visited[nx])sol(nx);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
ans=1e9;
    cin >> N >> K;
    adj=vector<vector<pi>>(N+1);
    for (int i = 0; i < N - 1; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        a++;b++;
        adj[a].push_back({b,c});
        adj[b].push_back({a,c});
    }
    sol(1);
    if(ans>=1e9)cout << -1;
    else cout << ans;
}