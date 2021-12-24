#include <bits/stdc++.h>
using namespace std;
using pi = pair<int,int>;
int T,N;
const int INF=1e9+7;
int dp[202020];

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>T;
    dp[1]=1;dp[2]=2;
    for(int i = 3; i <= 200000; i++){
        dp[i]=dp[i-1]+dp[i-2];
        dp[i]%=INF;
    }
    while(T--){
        cin>>N;
        cout << dp[N] << '\n';
    }
}