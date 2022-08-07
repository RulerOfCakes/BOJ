#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ti = tuple<int, int, int>;

int N, Q;
const int INF = 1e9;
int dp[302][302][302];
vector<ti> edges;

int main()
{
    cin.tie(0)->sync_with_stdio(0);

    cin >> N >> Q;

    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            cin >> dp[i][j][0];
            if (i != j && dp[i][j][0] == 0)
                dp[i][j][0] = INF;
        }
    }

    for (int k = 1; k <= N; k++)
    {
        for (int i = 1; i <= N; i++)
        {
            for (int j = 1; j <= N; j++)
            {
                dp[i][j][k] = min(dp[i][j][k - 1], dp[i][k][k - 1] + dp[k][j][k - 1]);
            }
        }
    }
    for (int i = 0; i < Q; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        cout << ((dp[b][c][a - 1] >= INF) ? -1 : dp[b][c][a - 1]) << '\n';
    }
}