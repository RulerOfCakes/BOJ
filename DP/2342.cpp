#include <bits/stdc++.h>
using namespace std;
int dp[101010][5][5];
vector<int> v;
int dist[5][5] = {
    {0, 2, 2, 2, 2},
    {0, 1, 3, 4, 3},
    {0, 3, 1, 3, 4},
    {0, 4, 3, 1, 3},
    {0, 3, 4, 3, 1}};
int sol(int x, int y, int cnt)
{
    if (cnt >= v.size())
        return 0;
    int &ret = dp[cnt][x][y];
    if (ret != -1)
        return ret;

    ret = min(sol(v[cnt], y, cnt + 1) + dist[x][v[cnt]], 
                sol(x, v[cnt], cnt + 1) + dist[y][v[cnt]]);
    return ret;
}
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    int a = 1;
    cin >> a;
    memset(dp, -1, sizeof(dp));
    while (a)
    {
        v.push_back(a);
        cin >> a;
    }
    cout << sol(0, 0, 0);
}