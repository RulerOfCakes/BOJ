#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int, int>;
using pl = pair<ll, int>;

const int MAX = 20002;
int V, E, S, P;
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

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int T;
    cin >> T;
    while (T--)
    {
        cin >> V >> E;
        a = vector<vector<int>>(MAX, vector<int>());
        SCC = vector<vector<int>>();
        sccidx = vector<int>(MAX, 0);
        memset(visited,0,sizeof(visited));
        memset(finished,0,sizeof(finished));

        for (int i = 0; i < E; i++)
        {
            int at, bt;
            cin >> at >> bt;
            a[at].push_back(bt);
        }
       

        for (int i = 1; i <= V; i++)
        {
            if (!visited[i])
                dfs(i);
        }
    
        vector<int> indeg(MAX, 0);
        vector<int> outdeg(MAX, 0);
        for(int i = 1; i <= V; i++){
            for(int nxt : a[i]){
                if(sccidx[nxt]==sccidx[i])continue;
                indeg[sccidx[nxt]]++;
                outdeg[sccidx[i]]++;
            }
        }
        int out = 0, in = 0;
        for(int i = 0; i < SCC.size(); i++){
            if(!indeg[i])in++;
            if(!outdeg[i])out++;
        }
        if(SCC.size()==1){
            cout << 0 << '\n';
            continue;
        }
        
        cout << max(out,in) << '\n';
    }
}