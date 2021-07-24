#include <bits/stdc++.h>

using namespace std;

int N;
const int MAX = 18;
int dp[100002][MAX + 1];
bool visited[100002];
vector<vector<int>> v;
//max colors = log(n)+1

int dfs(int root, int color)
{
    int &ret = dp[root][color];
    if (ret != -1)
        return ret;

    ret = color;

    for (auto next : v[root])
    {
        if (visited[next])
            continue;
        int tmp = 1e9;
        visited[next] = 1;
        for (int i = 1; i < 19; i++)
        {
            if (i != color)
            {
                tmp = min(tmp, dfs(next, i));
            }
        }
        ret+=tmp;
        visited[next]=false;
    }
    return ret;
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    memset(dp, -1, sizeof(dp));
    v = vector<vector<int>>(N + 1, vector<int>());
    for (int i = 1; i < N; i++)
    {
        int a, b;
        cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    v[0].push_back(1);

    cout << dfs(0, 0);
}