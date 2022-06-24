#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pl = pair<ll, ll>;
int N, M, T;
ll bx, by;
vector<int> adj[2020];
int match2[2020], match1[2020];
vector<int> visited;
ll dist(pl p1, pl p2)
{
    return (p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second);
}
bool dfs(int x)
{
    if (visited[x])
        return false;
    visited[x] = 1;

    for (int i : adj[x])
    {
        if (!match2[i] || dfs(match2[i]))
        {
            match2[i] = x;
            match1[x] = i;
            return true;
        }
    }
    return false;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin >> T;
    for (int t = 1; t <= T; t++)
    {
        cout << "Case #" << t << ": ";
        cin >> N;
        memset(match2, 0, sizeof(match2));
        memset(match1, 0, sizeof(match1));
        for (int i = 0; i <= N; i++)
            adj[i] = vector<int>();
        vector<int> vv;
        vector<pl> children(N + 1), candies(N + 1);
        for (int i = 1; i <= N; i++)
        {
            int a, b;
            vv.push_back(i);
            cin >> a >> b;
            children[i] = {a, b};
        }
        set<int> vs(vv.begin(), vv.end());
        for (int i = 1; i <= N + 1; i++)
        {
            int a, b;
            cin >> a >> b;
            if (i == 1)
                bx = a, by = b;
            else
                candies[i - 1] = {a, b};
        }
        vector<map<ll, set<int>>> ump(N + 2);
        for (int i = 1; i <= N; i++)
        {
            ll bdist = dist(children[i], {bx, by});
            for (int j = 1; j <= N; j++)
            {
                ll cdist = dist(children[i], candies[j]);
                if (cdist <= bdist)
                {
                    adj[i].push_back(j);
                    ump[i][cdist].insert(j);
                }
            }
            sort(adj[i].begin(), adj[i].end(), [&](int &i1, int &i2)
                 { return dist(children[i], candies[i1]) < dist(children[i], candies[i2]); });
        }
        int opcnt = 0;
        vector<int> vstd(N + 2);
        for (int i = 1; i <= N; i++)
        {
            visited = vector<int>(2020, 0);
            if (!dfs(i))
            {
                cout << "IMPOSSIBLE\n";
                goto nxt;
            }
        }
        cout << "POSSIBLE\n";
        // cout << endl;

        while (opcnt < N)
        {
            // cout << opcnt << endl;
            bool found = 0;
            for (int i : vs)
            {
                if (found)
                    break;
                auto iter = ump[i].begin();
                while (!found && iter != ump[i].end())
                {
                    set<int> &cs = iter->second;
                    if (cs.count(match1[i]))
                    {
                        cs.erase(match1[i]);
                        vstd[match1[i]] = 1;
                        found = 1;
                        vs.erase(i);
                        cout << i << ' ' << match1[i] + 1 << '\n';
                    }
                    else
                    {
                        auto siter = cs.begin();
                        while (siter != cs.end())
                        {
                            if (vstd[*siter])
                            {
                                siter = cs.erase(siter);
                            }
                            else
                                siter++;
                        }
                    }
                    if (cs.empty())
                        iter = ump[i].erase(iter);
                    else
                        break;
                    if (found)
                        break;
                }
            }
            assert(found);
            opcnt++;
        }

    nxt:
        // cout << endl;
        continue;
    }
}