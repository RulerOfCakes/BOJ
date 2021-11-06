#include <bits/stdc++.h>
using namespace std;
const int MOD = 9901;
int N;
int dp[100002];

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> N;
    dp[0]=1;
    dp[1]=3;
    for(int i = 2; i <= N; i++){
        dp[i]=2*dp[i-1]+dp[i-2];
        dp[i]%=MOD;
    }
    cout << dp[N];
}