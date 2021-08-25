#include <bits/stdc++.h>

using namespace std;

int N;
int dp[30][2002];
const int MOD = 1e9+7;
//multiples of 3 -> sum of all digits % 3 = 0
//multiples of 5 -> first digit is 0 or 5 -> fixed to 5 in this case

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    dp[2][1]=1;
    for(int i = 2; i <= N; i++){
        dp[0][i]=dp[1][i-1]+dp[2][i-1];
        dp[0][i]%=MOD;
        dp[1][i]=dp[0][i-1]+dp[2][i-1];
        dp[1][i]%=MOD;
        dp[2][i]=dp[0][i-1]+dp[1][i-1];
        dp[2][i]%=MOD;
    }
    cout << dp[0][N];
}