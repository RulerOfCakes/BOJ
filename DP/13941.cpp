#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using Edge = tuple<int, int, int>;
const int INF=1e9;
int N, K;
int dp[1<<20];
int arr[21][21];
int sol(int bt, int cnt){
    if(cnt>=N-K)return 0;
    if(dp[bt]!=INF)return dp[bt];
    int& ret=dp[bt];
    
    for(int i = 0; i < N; i++){
        if(!(bt&(1<<i)))continue;
        for(int j=0;j<N;j++){
            if((!(bt&(1<<j)))||(i==j))continue;
            assert(i!=j);
            int nbt=bt-(1<<i);
            ret=min(ret,sol(nbt,cnt+1)+arr[i][j]);
        }
    }

    return ret;
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N >> K;
    fill(dp,dp+(1<<N),INF);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin>>arr[i][j];
        }
    }

    cout << sol((1<<N)-1,0);
} 