#include <bits/stdc++.h>

using namespace std;
using ll = long long;
int N, M;
int dp[14 * 14][1 << 14];
char arr[14][14];
int COST[6][6] = {
    {100, 70, 40, 0, 0, 0},
    {70, 50, 30, 0, 0, 0},
    {40, 30, 20, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0}};

int sol(int cur, int state)
{

    if (cur >= N * M)
        return 0;

    int &ret = dp[cur][state];
    if (ret != -1)
        return ret;
    ret = 0;

    ret = max(ret, sol(cur + 1, state >> 1));

    if (state & 1)
    {
        ret = max(ret, sol(cur + 1, state >> 1));
    }
    else
    {
        if (cur + M < N * M)
        {
            ret = max(ret, sol(cur+1, (state>>1)|(1<<(M-1))) +
             COST[arr[cur/M][cur%M]-'A'][arr[cur/M+1][cur%M]-'A']);
        }

        if (((cur % M) != (M - 1)) && ((state & 2) == 0))
        {
            ret =max(ret, sol(cur+2, state>>2) + 
            COST[arr[cur/M][cur%M]-'A'][arr[cur/M][cur%M+1]-'A']);
        }
    }
    return ret;
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    M=N;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            cin >> arr[i][j];
        }
    }
    memset(dp, -1, sizeof(dp));
    cout << sol(0, 0);
}