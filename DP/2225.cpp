#include <bits/stdc++.h>
using namespace std;

int N,K;
int dp[402][402];
const int MOD = 1e9;
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> N >> K;
    dp[0][0]=1;
    for(int i = 1; i <= K; i++){
        for(int j = 0; j <= N; j++){
            for(int k = 0; k <= N; k++){
                dp[k+j][i]+=dp[k][i-1];
                dp[k+j][i]%=MOD;
            }
        }
    }
    cout << dp[N][K];
}