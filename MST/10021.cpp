#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
class edge
{
public:
    int u, v;
    int w;
    edge(int a, int b, int c)
    {
        u = a;
        v = b;
        w = c;
    }
    bool operator<(const edge &e) const
    {
        return w < e.w;
    }
    bool operator>(const edge &e) const
    {
        return w > e.w;
    }
};

int parent[2002],sz[2002];

int find(int node)
{
    if (node == parent[node])
    {
        return node;
    }
    return parent[node] = find(parent[node]);
}

void uni(int a, int b)
{
    int ar = find(a), br = find(b);

    parent[br] = ar;
    sz[ar]+=sz[br];
}

int dist(int x1, int y1, int x2, int y2)
{
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

int N, C;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin >> N >> C;
    vector<pi> coords(N);
    for(int i = 0; i <= N; i++)parent[i]=i,sz[i]=1;
    priority_queue<edge, vector<edge>, greater<edge>> ev;
    for (int i = 0; i < N; i++)
    {
        int a, b;
        cin >> a >> b;
        coords[i] = {a, b};
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            int cost =
                dist(coords[i].first, coords[i].second, coords[j].first, coords[j].second);
            if (cost >= C)
            {
                ev.push(edge(i, j, cost));
            }
        }
    }
    int ans = 0;
    while (!ev.empty())
    {
        int x, y;
        int weight;
        edge te = ev.top();
        x = te.u;
        y = te.v;
        weight = te.w;
        ev.pop();
        // cout << x  << ' ' << y  << ' ' << weight << endl;
        if (find(x) != find(y))
        {
            uni(x, y);
            ans += weight;
        }
    }
    if(sz[find(0)]<N)cout << -1;
    else
    cout << ans;
}