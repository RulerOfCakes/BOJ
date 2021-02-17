#include <bits/stdc++.h>

using namespace std;

int N, ans = 1;

int dp[1003];
int arr[1003];

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    for(int i = N; i >= 1; i--){
        cin >> arr[i];
    }
    dp[1] = arr[1];
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= i; j++){
            if(!dp[j] || arr[i] <= dp[j]){
                dp[j] = arr[i];
                ans = max(ans, j);
                break;
            }
        }
    }
    cout << ans;
}