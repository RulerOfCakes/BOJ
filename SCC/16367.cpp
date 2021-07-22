#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int, int>;
using pl = pair<ll, int>;

const int MAX = 10004;
int V, E, S, T;
int id;           // unique node id
int visited[MAX]; // visit/parent

bool finished[MAX];      // dfs completion check
vector<vector<int>> a;   // nodes
vector<vector<int>> SCC; // scc

vector<int> sccidx;

stack<int> s;

int dfs(int x)
{
    visited[x] = ++id;
    s.push(x);

    int parent = visited[x];

    for (int i = 0; i < a[x].size(); i++)
    {
        int y = a[x][i];

        if (visited[y] == 0)
        {
            parent = min(parent, dfs(y));
        }
        else if (!finished[y])
        {
            parent = min(parent, visited[y]);
        }
    }

    // scc found
    if (parent == visited[x])
    {
        vector<int> scc;

        while (1)
        {
            int t = s.top();
            s.pop();
            scc.push_back(t);
            sccidx[t] = SCC.size();
            finished[t] = true;
            if (t == x)
                break;
        }

        //sort(scc.begin(),scc.end());
        SCC.push_back(scc);
    }

    return parent;
}

int inverse(int n)
{
    return n % 2 ? n - 1 : n + 1;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> V >> E;

    a = vector<vector<int>>(MAX, vector<int>());
    SCC = vector<vector<int>>();
    sccidx = vector<int>(MAX, 0);
    memset(visited, 0, sizeof(visited));
    memset(finished, 0, sizeof(finished));
    //positives - odd, negatives - even(starting at 0)
    //true=red, false = blue
    for (int i = 0; i < E; i++)
    {
        char ac, bc, cc;
        int at, bt, ct;
        cin >> at >> ac >> bt >> bc >> ct >> cc;
        at = (ac == 'B') ? ((at - 1) * 2) : (at * 2 - 1);
        bt = (bc == 'B') ? ((bt - 1) * 2) : (bt * 2 - 1);
        ct = (cc == 'B') ? ((ct - 1) * 2) : (ct * 2 - 1);


        a[inverse(at)].push_back(bt);
        a[inverse(bt)].push_back(at);

        a[inverse(at)].push_back(ct);
        a[inverse(ct)].push_back(at);

        a[inverse(bt)].push_back(ct);
        a[inverse(ct)].push_back(bt);
    }
    

    for (int i = 0; i < 2 * V; i++)
    {
        if (!visited[i])
            dfs(i);
    }

    for (int i = 0; i < V; i++)
    {
        if (sccidx[i * 2] == sccidx[i * 2 + 1])
        {
            cout << "-1";
            return 0;
        }
    }

    //cout << "yes" << '\n';
    vector<int> ans(V + 2, -1);
    vector<pi> order;
    for (int i = 0; i < 2 * V; i++)
    {
        order.push_back({sccidx[i], i});
    }
    sort(order.begin(), order.end(), greater<pi>());
    for (pi p : order)
    {
        int cur = p.second;
        if (ans[(cur) / 2] == -1)
        {
            ans[(cur) / 2] = cur % 2 ? 0 : 1;
        }
    }
    for (int i = 0; i < V; i++)
    {
        cout << ((ans[i]==1)?'R':'B');
    }
}