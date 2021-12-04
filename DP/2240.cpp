#include <bits/stdc++.h>
using namespace std;
int T,W;
int dp[1002][32][2];
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> T >> W;
    //start with 0
    int ans = 0;
    dp[0][0][0]=1;
    dp[0][1][1]=1;
    for(int i = 1; i <= T; i++){
        int a;
        cin >> a;
        a--;
        for(int j = 0; j <= W; j++){
            if(dp[i-1][j][a]>0)
                dp[i][j][a]=max(dp[i][j][a],dp[i-1][j][a]+1);
            if(dp[i-1][j][(a+1)%2]>0)
                dp[i][j+1][a]=max(dp[i][j+1][a],dp[i-1][j][(a+1)%2]+1);

            dp[i][j][(a+1)%2]=dp[i-1][j][(a+1)%2];
            if(j>0)
            dp[i][j][(a+1)%2]=max(dp[i][j][(a+1)%2],dp[i-1][j-1][a]);

        }
    }
    for(int j = 0; j <= W; j++){
        ans=max({ans,dp[T][j][0]-1,dp[T][j][1]-1});
    }
    cout << ans;
}