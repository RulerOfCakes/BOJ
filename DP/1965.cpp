#include <bits/stdc++.h>

using namespace std;

int dp[1002];
int arr[1002];
int ans = 1;
int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int N;
    cin >> N;
    for(int i = 1; i <= N; i++){
        cin >> arr[i];
    }
    dp[1] = arr[1];
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            if(arr[i] <= dp[j]){
                dp[j] = arr[i];
                break;
            } else if(dp[j] == 0){
                dp[j] = arr[i];
                ans = j;
                break;
            }
        }
    }
    cout << ans;
}