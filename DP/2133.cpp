#include <bits/stdc++.h>

using namespace std;

int N;
int dp[32];

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    dp[2] = 3;
    dp[0] = 1;
    for(int i = 4; i <= N; i++){
        dp[i] = dp[i-2]*3;
        for(int j = 4; j <= i; j+=2){
            dp[i] += dp[i-j]*2;
        }
    }
    cout << dp[N];
    
}