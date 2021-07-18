#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int, int>;
using pl = pair<ll, int>;

const int MAX = 500002;
int V, E, S, P;
int id;           // unique node id
int visited[MAX]; // visit/parent

bool finished[MAX];      // dfs completion check
vector<vector<int>> a;   // nodes
vector<vector<int>> SCC; // scc
vector<int> sccmoney;
vector<int> sccidx;
vector<int> sccrestaurant;
vector<int> money;
vector<int> restaurant;


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
        int tmp=0, btmp = 0;
        
        while (1)
        {
            int t = s.top();
            s.pop();
            scc.push_back(t);
            tmp+=money[t];
            if(restaurant[t])btmp=1;
            sccidx[t] = SCC.size();
            finished[t] = true;
            if (t == x)
                break;
        }
        
        //sort(scc.begin(),scc.end());
        SCC.push_back(scc);
        sccrestaurant.push_back(btmp);
        sccmoney.push_back(tmp);
    }
    

    return parent;
}

int sol(vector<vector<int>>& v){
    priority_queue<pair<int, int>> pq;
    vector<int> tvisited(v.size()+2, 0);
    int ret = 0;
    pq.push({sccmoney[sccidx[S]],sccidx[S]});
    while(!pq.empty()){
        int cc, cx;
        tie(cc, cx) = pq.top();
        pq.pop();
        if(sccrestaurant[cx]){
            ret=max(ret,cc);
        }
        if(tvisited[cx]>=cc)continue;
        tvisited[cx]=cc;
        for(int nx : v[cx]){
            if(tvisited[nx]>=cc+sccmoney[nx])continue;
            pq.push({cc+sccmoney[nx],nx});
        }
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int T;

    cin >> V >> E;
    a = vector<vector<int>>(MAX, vector<int>());
    SCC = vector<vector<int>>();
    sccidx = vector<int>(MAX, 0);
    money = vector<int>(MAX);
    restaurant = vector<int>(MAX);

    
    for (int i = 0; i < E; i++)
    {
        int at, bt;
        cin >> at >> bt;
        a[at].push_back(bt);
    }
    for(int i = 1; i <= V; i++){
        cin >> money[i];
    }

    cin >> S >> P;
    for(int i = 0; i < P; i++){
        int at;
        cin >> at;
        restaurant[at]=1;
    }
    
    for (int i = 1; i <= V; i++)
    {
        if (!visited[i])
            dfs(i);
    }
    
    vector<vector<int>> scce(SCC.size()+2, vector<int>());
    for (int i = 1; i <= V; i++)
    {
        for (int nxt : a[i])
        {
            if (sccidx[nxt] == sccidx[i])
                continue;
            scce[sccidx[i]].push_back(sccidx[nxt]);
        }
    }
    
    cout << sol(scce);
    
    
}