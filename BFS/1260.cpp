#include <bits/stdc++.h>

using namespace std;
int N, M, V;
vector<vector<int>> v;
vector<int> bfsv;
bool dfsvisited[100002];

void dfs(int x)
{
    dfsvisited[x] = 1;
    cout << x << ' ';
    for (auto a : v[x])
    {
        if (!dfsvisited[a])
        {

            dfs(a);
        }
    }
}

void bfs(int x)
{
    queue<int> q;
    q.push(x);
    vector<bool> visited(N + 1, false);
    visited[x] = 1;
    while (!q.empty())
    {
        int cur = q.front();
        bfsv.push_back(cur);
        q.pop();

        for (auto a : v[cur])
        {
            if (!visited[a])
            {
                q.push(a);
                visited[a] = 1;
            }
        }
    }
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M >> V;
    v = vector<vector<int>>(N + 1, vector<int>());
    for (int i = 0; i < M; i++)
    {
        int a, b;
        cin >> a >> b;
        v[a].push_back(b); //쌍방향 그래프이므로
        v[b].push_back(a); //두 정점 모두 간선 추가
    }
    for (int i = 0; i < v.size(); i++)
    {
        sort(v[i].begin(), v[i].end());
    }
    dfs(V);

    cout << '\n';
    bfs(V);
    for (int i = 0; i < bfsv.size(); i++)
    {
        cout << bfsv[i] << ' ';
    }
}