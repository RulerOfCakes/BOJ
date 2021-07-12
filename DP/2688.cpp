#include <bits/stdc++.h>

using namespace std;

int T, N;

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> T;
    while(T--){
        cin >> N;
        vector<vector<long long>> dp(N+1,vector<long long>(10,0));
        for(int i = 0; i <= 9; i++){
            dp[1][i]=1;
        }
        for(int i = 2; i <= N; i++){
            long long psum = 0;
            for(int j = 0; j <= 9; j++){
                psum+=dp[i-1][j];
                dp[i][j] = psum;
            }
        }
        long long ans = 0;
        for(int i = 0; i <= 9; i++){
            ans += dp[N][i];
        }
        cout << ans << '\n';
    }
}