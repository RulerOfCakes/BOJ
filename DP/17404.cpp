#include <bits/stdc++.h>

using namespace std;

int N, T;
const int INF = 1e9;
int dp[1002][3];
int arr[1002][3];

int sol(int start){
    for(int i = 2; i < N; i++){
        for(int j = 0; j < 3; j++){
            dp[i][j]=min(dp[i-1][(j+1)%3],dp[i-1][(j+2)%3]) + arr[i][j];
        }
    }
    return min(dp[N-1][(start+1)%3],dp[N-1][(start+2)%3]);
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> arr[i][0] >> arr[i][1] >> arr[i][2];
    }
    int ans = INF;
    for(int i = 0; i < 3; i++){
        dp[1][i]=INF;
        dp[1][(i+1)%3]=arr[0][i]+arr[1][(i+1)%3];
        dp[1][(i+2)%3]=arr[0][i]+arr[1][(i+2)%3];
        ans=min(ans,sol(i));
        memset(dp,0,sizeof(dp));
    }
    cout << ans;
}