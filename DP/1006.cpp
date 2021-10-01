#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int T,N,W;
const int INF = 1e9;
vector<vector<int>> dp,enemy;

//dp[0][i]  **
//          *

//dp[1][i]  *
//          **

//dp[2][i]  **
//          **
void sol(){
    for(int i = 2; i <= N; i++){
        int outer = 2-(enemy[0][i]+enemy[0][i-1] <= W); //cost for two outer
        int inner = 2-(enemy[1][i]+enemy[1][i-1] <= W); //cost for two iner
        int cross = 2-(enemy[0][i]+enemy[1][i] <= W); //cost for one inner and one outer

        dp[0][i]=min(dp[2][i-1]+1,dp[1][i-1]+outer);
        dp[1][i]=min(dp[2][i-1]+1,dp[0][i-1]+inner);
        dp[2][i]=min({dp[2][i-1]+cross,dp[0][i]+1,dp[1][i]+1,dp[2][i-2]+inner+outer});
    }
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> T;
    while(T--){
        cin >> N >> W;
        dp=vector<vector<int>>(3,vector<int>(N+1,0));
        enemy=vector<vector<int>>(2,vector<int>(N+1));

        for(int i = 0; i < N; i++){
            cin >> enemy[0][i+1];
        }
        for(int i = 0; i < N; i++){
            cin >> enemy[1][i+1];
        }
        if(N==1){
            cout << ((enemy[0][1]+enemy[1][1]<=W)?1:2) << '\n';
            continue;
        }
        int ans = INF;

        dp[0][1]=dp[1][1]=1;
        dp[2][1]=2-(enemy[0][1]+enemy[1][1]<=W);
        sol();

        ans=min(ans,dp[2][N]);

        if(enemy[0][N]+enemy[0][1]<=W){
            //starting with outer
            dp[2][0]=INF;dp[0][1]=1;dp[1][1]=INF;
            dp[2][1]=2;
            sol();
            ans=min(ans,dp[1][N]);
        }
        if(enemy[1][N]+enemy[1][1] <= W){
            //inner
            dp[2][0]=INF;dp[1][1]=1;dp[0][1]=INF;
            dp[2][1]=2;
            sol();
            ans=min(ans,dp[0][N]);
        }
        if(enemy[0][N]+enemy[0][1] <= W && enemy[1][N]+enemy[1][1] <= W){
            dp[2][0]=INF; dp[0][1] = dp[1][1] = INF; dp[2][1]=2;
            sol();
            ans=min(ans,dp[2][N-1]);
        }

        cout << ans << '\n';
    }
}