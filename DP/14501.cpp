#include <bits/stdc++.h>

using namespace std;

int N;
int dp[22], utime[16], pay[16];

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N;
    for(int i = 0; i < N; i++){
        cin >> utime[i+1] >> pay[i+1];
    }
    
    for(int i = 1; i <= N; i++){
        dp[i] = max(dp[i], dp[i-1]);
        dp[i+utime[i]-1] = max(dp[i-1] + pay[i], dp[i+utime[i]-1]);
    }
    cout << dp[N];
}