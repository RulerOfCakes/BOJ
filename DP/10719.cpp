#include <bits/stdc++.h>
using namespace std;
int T,N,M,C;
int dp[101010][31];
int mins[101010];
int cost[31],order[101010];
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin>>T;
    while(T--){
        cin>>N>>M>>C;
        fill(mins,mins+N+1,1e9);
        for(int i = 1; i <= M; i++){
            cin>>cost[i];
        }
        for(int i =1; i <= N; i++){
            cin>>order[i];
        }
        cost[0]=0;order[0]=0;
        dp[0][0]=0;
        mins[0]=0;
        for(int j = 1; j <= M; j++){
            dp[0][j]=C;
        }
        for(int i = 1; i <= N; i++){
            for(int j = 0; j <= M; j++){
                if(order[i]==j){
                    dp[i][j]=min(mins[i-1]+C, dp[i-1][j]);
                }
                else{
                    dp[i][j]=min(dp[i-1][j]+cost[order[i]], mins[i-1]+C+cost[order[i]]);
                }
                mins[i]=min(mins[i],dp[i][j]);
            }
        }
        cout << mins[N] << '\n';
    }
}