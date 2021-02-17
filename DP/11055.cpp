#include <bits/stdc++.h>

using namespace std;

int N;

int dp[1003];
int arr[1003];

int ans = 0;

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    int a;
    for(int i = 0;i < N; i++){
        cin >> arr[i];
        dp[i] = arr[i];
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j <= i; j++){
            if(arr[j] < arr[i] && dp[i] < dp[j] + arr[i]){
                dp[i] = dp[j] + arr[i];
            }
        }
        ans = max(ans, dp[i]);
    }
    cout << ans;
    
}