#include <bits/stdc++.h>

using namespace std;

int N, K;
int dp[110002];
int arr[102];


int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> K;
    for(int i = 0; i < N; i++){
        cin >> arr[i];
        dp[arr[i]] = 1;
    }
    for(int i = 1; i < K; i++){
        if(!dp[i])continue;
        for(int j = 0; j < N; j++){
            if(dp[i+arr[j]])
            dp[i+arr[j]] = min(dp[i+arr[j]], dp[i]+1);
            else
            dp[i+arr[j]] = dp[i]+1;
        }
    }
    if(!dp[K]){
        cout << -1;
    }
    else{
        cout << dp[K];
    }
}