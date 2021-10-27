#include <bits/stdc++.h>

using namespace std;
int N;

int dp[502][502];
int arr[502][502];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

int dfs(int x, int y){
    if(dp[x][y]!=-1)return dp[x][y];
    int& ret = dp[x][y];
    ret=1;
    int val = arr[x][y];
    for(int i = 0; i < 4; i++){
        int nx = x+dx[i],ny=y+dy[i];
        if(nx<0||nx>=N||ny<0||ny>=N)continue;
        if(val>=arr[nx][ny])continue;
        ret=max(ret,dfs(nx,ny)+1);
    }
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    memset(dp,-1,sizeof(dp));
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> arr[i][j];
        }
    }
    int ans=0;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(dp[i][j]==-1)ans=max(ans,dfs(i,j));
        }
    }
    cout << ans;
}