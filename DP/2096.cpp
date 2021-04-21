#include <bits/stdc++.h>

using namespace std;
int N;

int dp[2][3];
int mindp[2][3];
int arr[2][3];
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    
    for(int i = 1; i <= N; i++){
        for(int j = 0; j < 3; j++){
            cin >> arr[i%2][j];
        }
        dp[i%2][0] = max(dp[(i-1)%2][0], dp[(i-1)%2][1]) + arr[i%2][0];
        dp[i%2][1] = max(dp[(i-1)%2][0], max(dp[(i-1)%2][1], dp[(i-1)%2][2])) + arr[i%2][1];
        dp[i%2][2] = max(dp[(i-1)%2][1], dp[(i-1)%2][2]) + arr[i%2][2];

        mindp[i%2][0] = min(mindp[(i-1)%2][0], mindp[(i-1)%2][1]) + arr[i%2][0];
        mindp[i%2][1] = min(mindp[(i-1)%2][0], min(mindp[(i-1)%2][1], mindp[(i-1)%2][2])) + arr[i%2][1];
        mindp[i%2][2] = min(mindp[(i-1)%2][1], mindp[(i-1)%2][2]) + arr[i%2][2];
    }
    cout << max(dp[N%2][0], max(dp[N%2][1], dp[N%2][2])) << ' ';
    cout << min(mindp[N%2][0], min(mindp[N%2][1], mindp[N%2][2]));
}