#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int, int>;

const ll INF = -1e12;
int N, M, C;
int money[1002];
ll dp[1002][1002];
vector<vector<int>> adj;
vector<pi> edges;

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M >> C;
    memset(dp, -1, sizeof(dp));
    adj = vector<vector<int>>(1002, vector<int>());
    for (int i = 1; i <= N; i++)
    {
        cin >> money[i];
    }
    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        edges.push_back({a,b});
    }
    ll ans = 0;
    dp[0][1]=0;
    for(int days=1; days<1002; days++){
        for(auto e : edges){
            int u = e.first;
            int v = e.second;
            if(dp[days-1][u]>=0){
                dp[days][v]=max(dp[days][v],dp[days-1][u]+money[u]);
            }
        }
        ans=max(ans,dp[days][1]-C*days*days);
    }
    cout << ans;
}