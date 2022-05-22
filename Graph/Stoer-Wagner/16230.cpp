#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using ll = long long;
// Stoer-Wagner gets the Global Min Cut of a connected graph in O(V^3)
vector<vector<int>> adj,badj;
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

priority_queue<int,vector<int>,greater<int>> components;
void bfs(int x){
    queue<int> q;
    q.push(x);
    visited[x]=1;
    int cnt=1;
    while(!q.empty()){
        int cx = q.front();
        q.pop();
        for(int i = 1; i <= N; i++){
            if(adj[cx][i]&&!visited[i]){
                visited[i]=1;
                cnt++;
                q.push(i);
            }
        }
    }
    components.push(cnt);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int T;

    cin >> N >> M;
    adj = vector<vector<int>>(N + 2, vector<int>(N + 2));
    // badj = vector<vector<int>>(N + 2, vector<int>(N + 2));
    dist = vector<int>(N + 2);
    deleted = vector<int>(N + 2);
    visited = vector<int>(N + 2);
    
    for (int i = 0; i < M; i++)
    {
        int a, b, c;
        cin >> a >> b;

        adj[a][b] = 1;
        adj[b][a] = 1;
    }
    int mc = getMinCut();
    if (mc)
    {
        cout << N - 1 << '\n';
        cout << N*(N-1)/2 - mc + 1;
    }
    else
    {
        dist=vector<int>(N+2);
        visited=vector<int>(N+2);
        for(int i = 1; i <= N; i++){
            if(!visited[i])bfs(i);
        }
        cout << components.top()*(N-components.top()) << '\n';
        cout << N*(N-1)/2 - components.size() + 2;
    }
}
