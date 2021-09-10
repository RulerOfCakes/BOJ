#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int INF = 1e9+7;
int dp[254][1<<14];
char arr[26][11];

int T, M, N;

int sol(int cur, int state)
{
    if ((cur == N * M) && (state == 0))
        return 0;
    if (cur >= N * M)
        return -INF;

    int &ret = dp[cur][state];
    if (ret != -1)
        return ret;
    int cx=cur/M,cy=cur%M;
    if(state&1){
        ret=sol(cur+1,(state>>1));
        return ret;
    }
    else
        ret = max(ret,sol(cur+1,(state>>1))+1);
    
    if(cx+1<N&&cy+1<M){
        if(arr[cx][cy]!='1'&&arr[cx][cy+1]!='1'&&arr[cx+1][cy]!='1'&&arr[cx+1][cy+1]!='1'){
            if((!(state&1))&&(!(state&2))&&(!(state&(1<<M)))&&(!(state&(1<<M+1))))
            {
                ret=max(ret,sol(cur+2,(state>>2)+(1<<M-2)+(1<<(M-1)))+16);
            }
        }
    }
    return ret;
}

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    
        cin >> M >> N;
        memset(dp,-1,sizeof(dp));
        for(int i = 0; i < M; i++){
            for(int j = 0; j < N; j++){
                cin >> arr[j][i];
            }
        }
        int state = 0;
        
        // for(int i = 0; i < M+2; i++){
        //     if(arr[i/M][i%M]=='1'){
        //         state|=(1<<(i));
        //     }
        // }
        cout << sol(0,state) << '\n';
    
    
}