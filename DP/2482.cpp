#include <bits/stdc++.h>
using namespace std;
int dp[1002][1002];
int N,K;
const int MOD = 1e9+3;
int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>N>>K;
    for(int i = 0; i <= N; i++){
        dp[i][1]=i;
        dp[i][0]=1;
    }
    for(int i = 2; i <= N; i++){
        for(int j = 2; j <= K; j++){
            dp[i][j]=(dp[i-2][j-1]+dp[i-1][j])%MOD;
        }
    }
    cout << (dp[N-3][K-1]+dp[N-1][K])%MOD;
}