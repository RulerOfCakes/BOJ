#include <bits/stdc++.h>

using namespace std;

int N, M;
int dp[1002][1002];
int arr[1002][1002];

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M;
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            char c;
            cin >> c;
            arr[i][j]=c-'0';
        }
    }
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            if(arr[i][j]){
                dp[i][j]=min({dp[i-1][j],dp[i][j-1],dp[i-1][j-1]})+1;
            }
        }
    }
    int ans = 0;
    for(int i = 1; i <= N; i++){
        for(int j = 1;j <= M; j++){
            ans=max(ans,dp[i][j]);
        }
    }
    cout << ans*ans;
}