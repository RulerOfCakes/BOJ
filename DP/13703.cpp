#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int N,K;
ll dp[65][128];
int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> K >> N;
    ll ans=0;
    dp[0][K]=1;
    
    for(int i = 1; i <= N; i++){
        dp[i][0]=dp[i-1][0]*2;
        for(int j = 0; j <= K+N; j++){
            if(j>1)
                dp[i][j]+=dp[i-1][j-1];
            
            dp[i][j]+=dp[i-1][j+1];
        }
    }
    cout << (1LL<<N)-dp[N][0];
}