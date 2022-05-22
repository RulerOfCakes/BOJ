#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using ll = long long;
// Stoer-Wagner gets the Global Min Cut of a connected graph in O(V^3)
vector<vector<int>> adj;
vector<int> dist, visited, deleted;
int N, M;

// min cut of s, t
int minCutPhase(int &s, int &t)
{
    fill(dist.begin(), dist.end(), 0);
    fill(visited.begin(), visited.end(), 0);
    int ret = 0;
    for (int i = 1; i <= N; i++)
    {
        int next = -1, cut = -1;
        for (int j = 1; j <= N; j++)
        {
            if (deleted[j] || visited[j])
                continue;
            if (dist[j] > cut)
            {
                next = j, cut = dist[j];
            }
        }
        if (next == -1)
            return ret;
        s = t, t = next;
        ret = cut;
        visited[next] = 1;
        for (int j = 1; j <= N; j++)
        {
            if (!deleted[j] && !visited[j])
                dist[j] += adj[next][j];
        }
    }
    return ret;
}

int getMinCut()
{
    int ret = INT_MAX;
    for (int i = 1; i < N; i++)
    {
        int s, t;
        int now = minCutPhase(s, t);
        deleted[t] = 1;
        ret = min(ret, now);
        if (!ret)
            return ret;
        for (int j = 1; j <= N; j++)
        {
            if (!deleted[j])
                adj[s][j] = (adj[j][s] += adj[j][t]);
        }
    }
    return ret;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int T;

    cin >> N >> M;
    adj = vector<vector<int>>(N + 2, vector<int>(N + 2));
    dist = vector<int>(N + 2);
    deleted = vector<int>(N + 2);
    visited = vector<int>(N + 2);
    for (int i = 0; i < M; i++)
    {
        int a, b, c;
        cin >> a >> b;
        c = 1;
        assert(a >= 1 && a <= N);
        assert(b >= 1 && b <= N);
        adj[a][b] += c;
        adj[b][a] += c;
    }
    cout << getMinCut();
}
