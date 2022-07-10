#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int N, M;
vector<vector<int>> adj;
int l[250250], r[250250], sz[250250];
ll psum[250250];
vector<vector<int>> colors;
int cnt = 0;
int dfs1(int cx, int prt)
{
    l[cx] = ++cnt;
    sz[cx] = 1;
    for (int nx : adj[cx])
    {
        if (nx == prt)
            continue;
        sz[cx] += dfs1(nx, cx);
    }
    r[cx] = cnt;
    return sz[cx];
}
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    vector<int> v(N + 2);
    colors.resize(N + 2);
    adj.resize(N + 2);
    for (int i = 1; i <= N; i++)
    {
        cin >> v[i];
    }
    for (int i = 1; i < N; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs1(1, 0);
    for (int i = 1; i <= N; i++)
    {
        colors[v[i]].push_back(l[i]);
    }

    for (int i = 1; i <= N; i++)
    {
        sort(colors[i].begin(), colors[i].end());
    }

    for (int i = 1; i <= N; i++)
    {
        int color = v[i];
        for (int nx : adj[i])
        {
            if (l[nx] < l[i])
            {
                // nx is parent (this happens only once)
                if (colors[color].front() < l[i] || colors[color].back() > r[i])
                {
                    // colored node is outside i's domain = out of i's subtree
                    psum[l[i]]++;
                    psum[r[i] + 1]--;
                }
            }
            else
            {
                // nx is child
                if (lower_bound(colors[color].begin(), colors[color].end(), l[nx]) != upper_bound(colors[color].begin(), colors[color].end(), r[nx]))
                {
                    psum[1]++;
                    psum[l[nx]]--;
                    psum[r[nx] + 1]++;
                }
            }
        }
    }

    for (int i = 1; i <= N; i++)
        psum[i] += psum[i - 1];

    ll ans1 = 0, ans2 = 0, ans3 = 0;
    for (int i = 1; i <= N; i++)
    {
        if (!psum[l[i]])
            ans1++, ans2 += i, ans3 += (ll)i * i;
    }
    cout << ans1 << '\n'
         << ans2 << '\n'
         << ans3;
}