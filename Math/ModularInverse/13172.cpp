#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<int, int>;
using pl = pair<ll, ll>;

const ll MOD = 1e9 + 7;

ll pow(ll n, ll m)
{
    ll ret = 1;
    while (m)
    {
        if (m & 1)
            ret = ret * n % MOD;
        m >>= 1;
        n = n * n % MOD;
    }
    return ret;
}

int N, T, M;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    vector<pl> v(N);
    ll ans = 0;
    for (int i = 0; i < N; i++)
    {
        cin >> v[i].first >> v[i].second;
        ll inv = pow(v[i].first, MOD - 2);
        ans += (inv * v[i].second) % MOD;
        ans %= MOD;
    }
    cout << ans;
}