#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int N,M;
ll dp[3][1002][102];
const int MOD = 998244353;
int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>N>>M;
    if(N==1){
        cout << M;
        return 0;
    }
    for(int i = 2; i <= N; i++){
        for(int j = 1; j <= M; j++){
            if(i==2){
                dp[0][i][j] = M-j;
                dp[1][i][j] = 1;
                dp[2][i][j] = j-1;
                dp[0][i][j]+=dp[0][i][j-1];
                dp[1][i][j]+=dp[1][i][j-1];
                dp[2][i][j]+=dp[2][i][j-1];
                continue;
            }
            //declining
            dp[0][i][j]=(dp[0][i-1][M]+MOD-dp[0][i-1][j])%MOD+
            (dp[1][i-1][M]+MOD-dp[1][i-1][j])%MOD;
            dp[0][i][j]+=dp[0][i][j-1];
            dp[0][i][j]%=MOD;
            //s a m
            dp[1][i][j]=(dp[1][i-1][j]-dp[1][i-1][j-1]+MOD)%MOD +
             (dp[0][i-1][j]-dp[0][i-1][j-1]+MOD)%MOD +
              (dp[2][i-1][j]-dp[2][i-1][j-1]+MOD)%MOD;
            dp[1][i][j]+=dp[1][i][j-1];
            dp[1][i][j]%=MOD;
            //inclining
            dp[2][i][j]=dp[0][i-1][j-1]+dp[2][i-1][j-1]+dp[1][i-1][j-1];
            dp[2][i][j]+=dp[2][i][j-1];
            dp[2][i][j]%=MOD;
        }
    }
    cout << ((dp[0][N][M]+dp[1][N][M])%MOD+dp[2][N][M])%MOD;
}