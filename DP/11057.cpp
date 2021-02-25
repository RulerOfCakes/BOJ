#include <bits/stdc++.h>

using namespace std;

int N, M;
int dp[1002][10];


int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    for(int i = 0; i <= 9; i++){
        dp[1][i] = 1;
    }
    for(int i = 2; i <= N; i++){
        for(int j = 0; j <= 9; j++){
            if(j == 0){
                dp[i][j] = dp[i-1][j] % 10007;
                continue;
            }
            for(int k = 0; k <= j; k++){
                dp[i][j] += dp[i-1][k];
                dp[i][j] %= 10007;
            }
        }
    }
    int ans = 0;
    for(int i = 0; i <= 9; i++){
        ans += dp[N][i];
        ans %= 10007;
    }
    cout << ans;
}