#include <bits/stdc++.h>

using namespace std;

int N;
const int INF = 1e9;
int arr[17][17];
int dp[17][1<<16];

int solve(int cur, int vsted){
    if(vsted == (1<<N)-1){
        if(arr[cur][0]==0){
            return INF;
        }
        return arr[cur][0];
    }
    if(dp[cur][vsted]){
        return dp[cur][vsted];
    }

    dp[cur][vsted] = INF;
    for(int i = 0; i < N; i++){
        int next = 1<<i;
        if(!arr[cur][i]||(vsted&next)>0)continue;
        dp[cur][vsted] = min(dp[cur][vsted], solve(i, vsted|next) + arr[cur][i]);
    }
    return dp[cur][vsted];
}

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin >> arr[i][j];
        }
    }
    cout << solve(0, 1);
}