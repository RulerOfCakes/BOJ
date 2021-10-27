#include <bits/stdc++.h>

using namespace std;
using pi = pair<int,int>;
using ll = long long;

int N, M;
int arr[502][502];
int dp[502][502];
int dx[]={0,0,-1,1};
int dy[]={1,-1,0,0};

int dfs(int sx,int sy){
    if(sx==N-1&&sy==M-1)return 1;
    int& ret= dp[sx][sy];
    if(ret!=-1)return ret;
    ret=0;
    int sval = arr[sx][sy];
    for(int i = 0 ; i < 4; i++){
        int nx=sx+dx[i],ny=sy+dy[i];
        if(nx<0||nx>=N||ny<0||ny>=M)continue;
        int nval=arr[nx][ny];
        if(sval<=nval)continue;
        ret+=dfs(nx,ny);
    }

    return ret;
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin >> N >> M;
    memset(dp,-1,sizeof(dp));
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> arr[i][j];
        }
    }

    cout << dfs(0,0);
}