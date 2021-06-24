#include <bits/stdc++.h>

using namespace std;

int T, N;
int dp[1002][1002];
int arr[1002];

int sol(int sx, int sy, int p){
    if(dp[sx][sy] > 0)return dp[sx][sy];
    if(p){
        if(sx==sy)return dp[sx][sy]=0;
        return dp[sx][sy]=min(sol(sx+1, sy, p^1), sol(sx, sy-1, p^1));
    }else{
        if(sx==sy)return dp[sx][sy]=arr[sx];
        return dp[sx][sy]=max(sol(sx+1, sy, p^1)+arr[sx], sol(sx, sy-1, p^1)+arr[sy]);
    }
}

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> T;
    while(T--){
        cin >> N;
        memset(dp, 0, sizeof(dp));
        for(int i = 0; i < N; i++){
            cin>>arr[i];
        }
        cout << sol(0, N-1, 0) << '\n';
    }
}