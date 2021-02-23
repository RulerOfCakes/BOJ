#include <bits/stdc++.h>

using namespace std;

int N;
int dp[1002];

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N;
    dp[1] = 1;
    dp[2] = 3;
    for(int i = 3; i <= N; i++){
        dp[i] = (dp[i-1] + 2*dp[i-2]) % 10007;
    }
    cout << dp[N] % 10007;
}