#include <bits/stdc++.h>

using namespace std;
using ll = long long;
int N, M;
int arr[102];
ll dp[102][21];


int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    for(int i = 0; i < N; i++){
        cin >> arr[i];
    }
    dp[0][arr[0]] = 1;
    for(int i = 1; i < N-1; i++){
        for(int j = 0; j <= 20; j++){
            if(j-arr[i] >= 0)
            dp[i][j] += dp[i-1][j-arr[i]];
            if(j+arr[i] <= 20)
            dp[i][j] += dp[i-1][j+arr[i]];
        }
    }
    
    cout << dp[N-2][arr[N-1]];
    
}