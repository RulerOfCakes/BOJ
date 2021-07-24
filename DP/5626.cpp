#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int N;
const ll MOD = 1000000007;
ll dp[2][10002]; //cur height
int arr[10002];  //input heights

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
        if (arr[i] != -1)
            arr[i]++; //to differentiate -1 when calculating dp
    }
    dp[0][1] = (arr[0] == -1 || arr[0] == 1) ? 1 : 0;
    for (int i = 1; i < N; i++)
    {
        int cur = i % 2, prev = (cur+1)%2;
        memset(dp[cur],0,sizeof(dp[cur]));
        if(arr[i]==-1){
            for (int j = 1; j <= N; j++)
            {
                dp[cur][j] = (dp[prev][j - 1] + dp[prev][j] + dp[prev][j + 1]) % MOD;
            }
        } else {
            dp[cur][arr[i]]=(dp[prev][arr[i]-1]+dp[prev][arr[i]]+dp[prev][arr[i]+1])%MOD;
        }
    }
    cout << dp[(N%2+1)%2][1];
}