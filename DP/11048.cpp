#include <bits/stdc++.h>

using namespace std;

int N, M;
int dp[1002][1002];
int arr[1002][1002];

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> arr[i][j];
        }
    }
    dp[0][0] = arr[0][0];
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            if(i-1 >=0 && j-1 >= 0){
                dp[i][j] = max(dp[i][j], dp[i-1][j-1] + arr[i][j]);
            }
            if(i-1 >= 0 && j >= 0){
                dp[i][j] = max(dp[i][j], dp[i-1][j] + arr[i][j]);
            }
            if(i >= 0 && j-1 >= 0){
                dp[i][j] = max(dp[i][j], dp[i][j-1] + arr[i][j]);
            }
        }
    }
    cout << dp[N-1][M-1];
}