
#include <bits/stdc++.h>

using namespace std;
using pi = pair<int, int>;

const int MAXPARENT = 18;
int N, M;
int parent[100002][18];
int depth[100002];
vector<int> adj[100002];

//initializing base parent and depths
void initTree(int x)
{
    for (int next : adj[x])
    {
        if (depth[next] == -1)
        {
            parent[next][0] = x;
            depth[next] = depth[x] + 1;
            initTree(next);
        }
    }
}

int lca(int a, int b)
{
    if (depth[a] < depth[b])
        swap(a, b);
    int diff = depth[a] - depth[b];

    //getting rid of depth diff
    for (int j = 0; diff; j++)
    {
        if (diff % 2)
            a = parent[a][j];
        diff /= 2;
    }

    if (a != b)
    {
        for (int j = MAXPARENT - 1; j >= 0; j--)
        {
            if (parent[a][j] != -1 && parent[a][j] != parent[b][j])
            {
                a = parent[a][j];
                b = parent[b][j];
            }
        }
        a = parent[a][0];
    }
    return a;
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    for (int i = 0; i < N - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    fill(depth, depth + N + 1, -1);
    memset(parent, -1, sizeof(parent));
    depth[1] = 0;
    initTree(1);
    //1 is the root
    for (int j = 0; j < MAXPARENT - 1; j++)
    {
        for (int i = 2; i <= N; i++)
        {
            if (parent[i][j] != -1)
            {
                parent[i][j + 1] = parent[parent[i][j]][j];
            }
        }
    }

    cin >> M;
    for (int i = 0; i < M; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        int ans1 = lca(a,b), ans2 = lca(a, c), ans3 = lca(b, c);
        int ans = ans1;
        //cout << ans1 << ' ' << ans2 << ' '<< ans3 << '\n';
        //deepest depth = ans
        if(depth[ans2]>depth[ans])ans=ans2;
        if(depth[ans3]>depth[ans])ans=ans3;
        cout << ans << '\n';
    }
}