#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int N, S, M;
bool dp[102][1002];
int arr[102];

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> S >> M;
    dp[0][S]=1;
    for(int i = 1; i <= N; i++){
        cin >> arr[i];
        for(int j = 0; j <= M; j++){
            if(dp[i-1][j]){
                if(j+arr[i]<=M)dp[i][j+arr[i]]=1;
                if(j-arr[i]>=0)dp[i][j-arr[i]]=1;
            }
        }
    }
    
    int ans = -1;
    for(int i = 0; i <= M; i++){
        if(dp[N][i])ans=i;
    }
    cout << ans;
}