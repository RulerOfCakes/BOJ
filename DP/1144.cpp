#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MOD = 1e9+7;
int arr[10][10];
vector<map<int,int>>dp(100,map<int,int>());
int up=1;
int N, M;

int sol(int cur, int state){
    if((cur==N*M)&&(state==0))return 0;
    
    if(dp[cur].find(state)!=dp[cur].end()){
        return dp[cur][state];
    }
    int& ret = dp[cur][state]=MOD;
    int upstate=state/up;
    //might be an exception at M=1
    if(!((upstate!=0)&&((up>=10)&&((state%up)/(up/10)==0)))){
        ret=sol(cur+1,state/=10);
    }
    
    
}

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N >> M;
    for(int i = 1; i < M; i++){
        up*=10;
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> arr[i][j];
        }
    }
    cout << sol(0,0);
}