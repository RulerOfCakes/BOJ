#include <bits/stdc++.h>

using namespace std;
using ll = long long;
int T, N, M;
const int MOD = 1e9+9;
vector<vector<int>> dp;
int prev(int i, int x){
    if(i==0)return 1;
    int ret=0;
    for(int k = 0; k < 3; k++){
        if(k+1==x)continue;
        ret+=dp[i][k];
        ret%=MOD;
    }
    return ret;
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> T;
    dp=vector<vector<int>>(100001,vector<int>(3,0));
        dp[0][0]=1;
        for(int i = 1; i <= 100000; i++){
            if(i-1>=0){
                dp[i][0]=prev(i-1,1);
                dp[i][0]%=MOD;
            }
            if(i-2>=0){
                dp[i][1]=prev(i-2,2);
                dp[i][1]%=MOD;
            }
            if(i-3>=0){
                dp[i][2]=prev(i-3,3);
                dp[i][2]%=MOD;
            }
        }
        
    while(T--){
        cin >> N;
        cout << (((dp[N][0]+dp[N][1])%MOD)+dp[N][2])%MOD << '\n';
    }
}