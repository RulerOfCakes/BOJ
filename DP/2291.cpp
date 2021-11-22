#include <bits/stdc++.h>
using namespace std;
int N,M,K;
int dp[12][422][422];

int sol(int len, int sum, int minn){
    if(len>N||sum>M)return 0;
    if(dp[len][sum][minn]!=-1)return dp[len][sum][minn];
    int& ret = dp[len][sum][minn];
    ret=0;
    for(int i = minn; i <= M; i++){
        if(i+sum>M)break;
        ret+=sol(len+1,sum+i,i);
    }
    return ret;
}
void ans(int len, int sum, int minn, int idx){
    if(len==N)return;
    for(int i = minn; i <= M; i++){
        int tmp = dp[len+1][sum+i][i];
        if(tmp==-1)continue;
        if(tmp<idx){
            idx-=tmp;
            continue;
        }
        cout << i << ' ';
        ans(len+1,sum+i,i,idx);
        break;
    }
}
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin >> N >> M >> K;
    memset(dp,-1,sizeof(dp));
    for(int i = 1; i <= M; i++)dp[N][M][i]=1;
    sol(0,0,1);
    ans(0,0,1,K);
}