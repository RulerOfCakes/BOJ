#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<int,int>;
const int MOD = 5e6;
int N, K;
int dp[102][10002];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N >> K;
    vector<int> cost, score;
    cost.push_back(0);score.push_back(0);
    for(int i = 0; i < N; i++){
        int a,b;
        cin>> a>>b;
        cost.push_back(a);
        score.push_back(b);
    }
    
    for(int i = 1; i <= N; i++){
        for(int j = 0; j <= K; j++){
            if(j>=cost[i])
                dp[i][j]=max(dp[i-1][j],dp[i-1][j-cost[i]]+score[i]);
            else
                dp[i][j]=dp[i-1][j];
        }
    }
    int ans = 0;
    for(int i = K; i >= 0; i--){
        ans=max(ans,dp[N][i]);
    }
    cout << ans;
}