#include <bits/stdc++.h>

using namespace std;

int N, M;
int arr[1025][1025];
int dp[1025][1025];


int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M;
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            cin >> arr[i][j];
        }
    }
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            dp[i][j] = dp[i][j-1] + arr[i][j];
        }
    }
    for(int i = 0; i < M; i++){
        int x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        int tempsum = 0;
        for(int j = x1; j <= x2; j++){
            tempsum += dp[j][y2] - dp[j][y1-1];
        }
        cout << tempsum << '\n';
    }
    
}