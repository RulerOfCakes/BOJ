#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int, int>;
int N, M, K, S, T;
const ll INF = 1e15;
vector<vector<pi>> v;
vector<vector<int>> lift;
ll dp[100002][11];

ll sol(int x, int k)
{
    if (k < 0)
        return -INF;
    ll &ret = dp[x][k];
    if (ret != -1)
        return ret;
    ret=-INF;
    if (x == T && k == 0)
    {
        return ret = 0;
    }
    else if(x==T){
        ret=0;
    }

    for (auto p : v[x])
    {
        int nx = p.first;
        ll nc = p.second;

        ret = max(ret, sol(nx, k) + nc);
        
    }
    if (k > 0)
    {
        for (auto i : lift[x])
        {
            ret = max(ret, sol(i, k - 1));
           
        }
    }


    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M >> K >> S >> T;
    v = vector<vector<pi>>(N + 1, vector<pi>());
    lift = vector<vector<int>>(N + 1, vector<int>());

    memset(dp, -1, sizeof(dp));
    for (int i = 0; i < M; i++)
    {
        int a, b, t;
        cin >> a >> b >> t;
        v[a].push_back({b, t});
        lift[b].push_back(a);
    }
    ll ans = sol(S, K);
    if(ans<0)cout << -1;
    else cout << ans;
}