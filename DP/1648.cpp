#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MOD = 9901;
int dp[14*14][1<<14];

int N, M;

int sol(int cur, int state){
    if((cur==N*M)&&(state==0))return 1;
    if(cur>=N*M)return 0;

    int& ret = dp[cur][state];
    if(ret!=-1)return ret;
    ret=0;
    
    if(state&1){
        ret=sol(cur+1, (state>>1));
    } else {
        ret = sol(cur+1, ((state>>1)|(1<<(M-1))));

        if(((cur%M)!=(M-1)) && (((state&2)==0)&&((state&1)==0))){
            ret+=sol(cur+2, (state>>2));
        }
    }
    return ret%=MOD;
}

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N >> M;
    memset(dp, -1, sizeof(dp));
    cout << sol(0, 0) << '\n';
    
}