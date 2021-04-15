#include <bits/stdc++.h>

using namespace std;
int N;

int dp[100001][2];
int arr[100002];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
    }
    int ans = INT_MIN;
    dp[0][0] = arr[0];
    dp[0][1] = max(arr[0], 0);
    ans = arr[0];
    for(int i = 1; i < N; i++){
        dp[i][0] = max(arr[i], dp[i-1][0] + arr[i]);
        dp[i][1] = max(dp[i-1][1] + arr[i], dp[i-1][0]);
        ans = max(ans, max(dp[i][0], dp[i][1]));
    }
    
    cout << ans;
}