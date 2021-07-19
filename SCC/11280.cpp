#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int, int>;
using pl = pair<ll, int>;

const int MAX = 20004;
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
    //positives - odd, negatives - even(starting at 0)
    for (int i = 0; i < E; i++)
    {
        int at, bt;
        cin >> at >> bt;
        at = (at < 0) ? (-(at + 1) * 2) : (at * 2 - 1);
        bt = (bt < 0) ? (-(bt + 1) * 2) : (bt * 2 - 1);

        a[inverse(at)].push_back(bt);
        a[inverse(bt)].push_back(at);
    }

    for (int i = 0; i < 2 * V; i++)
    {
        if (!visited[i])
            dfs(i);
    }
    for (int i = 0; i < V; i++)
    {
        if(sccidx[i*2]==sccidx[i*2+1]){
            cout << 0;
            return 0;
        }
    }
    cout << 1;
}