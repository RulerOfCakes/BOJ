#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int N;
int STR[51], INT[51], PNT[51];
int dp[1002][1002];//amount of quests completed
int points[1002][1002];//amount of points left after reaching this state
int possible[1002][1002];//whether reaching a state is possible or not
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> STR[i] >> INT[i] >> PNT[i];
    }
    for (int i = 1; i <= 1000; i++)
    {
        for (int j = 1; j <= 1000; j++)
        {
            int psum = 0;
            for (int k = 0; k < N; k++)
            {
                if (STR[k] <= i || INT[k] <= j)
                {
                    psum += PNT[k];
                    dp[i][j]++;
                }
            }
            points[i][j] = psum - (i - 1) - (j - 1);
            if (i == 1 && j == 1)
            {
                possible[i][j] = 1;
                continue;
            }
            if (i - 1 > 0 && possible[i - 1][j] && points[i - 1][j])
            {
                possible[i][j] = 1;
                continue;
            }
            if (j - 1 > 0 && possible[i][j - 1] && points[i][j - 1])
            {
                possible[i][j] = 1;
                continue;
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= 1000; i++)
    {
        for (int j = 1; j <= 1000; j++)
        {
            if(possible[i][j]){
                ans=max(ans,dp[i][j]);
            }
        }
    }
    cout << ans;
}