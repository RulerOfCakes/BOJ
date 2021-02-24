#include <bits/stdc++.h>

using namespace std;

int N, T;
int dp[100002][2];
int arr[100002][2];

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> T;
    while(T--){
        int ans = 0;
        cin >> N;
        memset(dp, 0, sizeof(dp));
        memset(arr, 0, sizeof(arr));
        for(int i = 0; i < N; i++){
            cin >> arr[i][0];
        }
        for(int i = 0; i < N; i++){
            cin >> arr[i][1];
        }
        dp[0][0] = arr[0][0];dp[0][1] = arr[0][1];
        dp[1][0] = arr[1][0] + arr[0][1];dp[1][1] = arr[1][1] + arr[0][0];
        for(int i = 2; i < N; i++){
            dp[i][0] = max(dp[i-1][1], dp[i-2][1]) + arr[i][0];
            dp[i][1] = max(dp[i-1][0], dp[i-2][0]) + arr[i][1];
            ans = max(ans, max(dp[i][0], dp[i][1]));
        }
        cout << ans << '\n';
    }
}