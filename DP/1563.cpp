#include <bits/stdc++.h>

using namespace std;

int N, T;
const int MOD = 1e6;
int dp[1002][3][4];
//late / absent

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    dp[1][0][0]=1;
    dp[1][1][0]=1;
    dp[1][0][1]=1;
    for(int i = 2; i <= N; i++){
        dp[i][0][0]=dp[i-1][0][0]+dp[i-1][0][2]+dp[i-1][0][1];
        dp[i][0][0]%=MOD;
        dp[i][0][1]=dp[i-1][0][0];
        dp[i][0][2]=dp[i-1][0][1];
        dp[i][1][0]=dp[i-1][1][0]+dp[i-1][1][1]+dp[i-1][1][2]+dp[i][0][0];
        dp[i][1][0]%=MOD;
        dp[i][1][1]=dp[i-1][1][0];
        dp[i][1][2]=dp[i-1][1][1];
    }
    int ans=0;
    for(int i = 0; i < 2; i++){
        for(int j = 0;j  < 3; j++){
            ans+=dp[N][i][j];
            ans%=MOD;
        }
    }
    cout << ans;
}