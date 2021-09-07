#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
const int INF = 1e9 + 7;
class Edge
{
public:
    int from, to, cap, flow;
    Edge *reverse;
    Edge() : from(0), to(0), cap(0), flow(0), reverse(nullptr) {}
    Edge(const Edge &e) : from(e.from), to(e.to), cap(e.cap), flow(e.flow), reverse(e.reverse) {}
    Edge(int from, int to, int cap) : from(from), to(to), cap(cap), flow(0), reverse(nullptr) {}
};
class DinicFlow
{
public:
    int N, source, sink;
    vector<vector<Edge *>> adj;
    vector<int> level;
    queue<int> bq;
    vector<int> work;
    DinicFlow() : N(0), source(0), sink(0), adj(), level(), bq(), work() {}
    DinicFlow(const DinicFlow &df) : N(df.N), source(df.source), sink(df.sink), adj(df.adj), level(df.level), bq(df.bq), work(df.work) {}
    DinicFlow(int N, int source, int sink) : N(N), source(source), sink(sink), adj(N), level(N), bq(), work(N) {}

    void add_edge(int from, int to, int cap)
    {
        Edge *e = new Edge(from, to, cap);
        Edge *e_reverse = new Edge(to, from, 0);
        e->reverse = e_reverse;
        e_reverse->reverse = e;
        adj[from].push_back(e);
        adj[to].push_back(e_reverse);
    }

    bool levelling()
    {
        level = vector<int>(N, -1);
        level[source] = 0;
        bq = queue<int>();
        bq.push(source);
        while (!bq.empty())
        {
            int now = bq.front();
            bq.pop();
            for (auto e : adj[now])
            {
                if (level[e->to] == -1 && e->cap > 0)
                {
                    level[e->to] = level[now] + 1;
                    bq.push(e->to);
                }
            }
        }
        return (level[sink] != -1);
    }

    int dfs(int cx, int mf)
    {
        if (cx == sink)
        {
            return mf;
        };

        for (int &i = work[cx]; i < adj[cx].size(); i++)
        {
            auto e = adj[cx][i];
            if (level[e->to] == level[cx] + 1 && e->cap > 0)
            {
                int flow = dfs(e->to, min(mf, e->cap));
                if (flow)
                {
                    e->cap -= flow;
                    e->reverse->cap += flow;
                    e->flow += flow;
                    e->reverse->flow -= flow;
                    return flow;
                }
            }
        }
        return 0;
    }

    int max_flow()
    {
        int ret = 0;
        while (levelling())
        {
            work = vector<int>(N);
            int flow = 0;
            while (flow = dfs(source, INT_MAX))
                ret += flow;
        }
        return ret;
    }
    ~DinicFlow()
    {
        for (auto &i : adj)
        {
            for (auto &e : i)
            {
                delete e;
            }
        }
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, M;

    cin >> N >> M;

    int source = 0, sink = 2*N*M + 4;
    DinicFlow df(2*N*M+5, source, sink);
    vector<vector<char>> v(N + 3, vector<char>(M + 3));
    vector<vector<int>> node_row(N + 3, vector<int>(M + 3));
    vector<vector<int>> node_col(N + 3, vector<int>(M + 3));

    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            cin >> v[i][j];
        }
    }

    int nodeidx = 1;
    //columns first
    for (int i = 1; i <= N; i++)
    {
        df.add_edge(source, nodeidx, 1);
        for (int j = 1; j <= M; j++)
        {
            if (v[i][j] == '.')
            {
                nodeidx++;
                df.add_edge(source, nodeidx, 1);
                continue;
            }
            node_row[i][j] = nodeidx;
        }
        nodeidx++;
    }

    //rows next
    for (int i = 1; i <= M; i++)
    {
        df.add_edge(nodeidx, sink, 1);
        for (int j = 1; j <= N; j++)
        {
            if (v[j][i] == '.')
            {
                nodeidx++;
                df.add_edge(nodeidx, sink, 1);
                continue;
            }
            node_col[j][i] = nodeidx;
        }
        nodeidx++;
    }

    //now connecting the individual nodes
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            if (v[i][j] == '*')
            {
                //since we're only flowing 1 to each 'node'
                //doesnt matter if we have duplicate edges
                df.add_edge(node_row[i][j], node_col[i][j], 1);
            }
        }
    }

    cout << df.max_flow();
}