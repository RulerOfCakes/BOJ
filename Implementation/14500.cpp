#include <bits/stdc++.h>
using namespace std;
int N,M;
int arr[502][502];
bool visited[502][502];
int dx[]={0,0,-1,1};
int dy[]={1,-1,0,0};
int dfs(int x, int y, int cnt){
    if(cnt>=3)return arr[x][y];
    visited[x][y]=1;
    int ret=arr[x][y];
    for(int i = 0; i < 4; i++){
        int nx=x+dx[i],ny=y+dy[i];
        if(nx<=0||nx>N||ny<=0||ny>M)continue;
        if(visited[nx][ny])continue;
        ret=max(ret,arr[x][y]+dfs(nx,ny,cnt+1));
    }
    visited[x][y]=0;
    return ret;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>N>>M;
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= M; j++){
            cin >> arr[i][j];
        }
    }
    int ans=0;
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= M; j++){
            ans=max(ans,dfs(i,j,0));
            int tmp=arr[i][j]+arr[i+1][j]+arr[i][j+1]+arr[i-1][j]+arr[i][j-1];
            for(int k = 0; k < 4; k++){
                int nx=i+dx[k],ny=j+dy[k];
                ans=max(ans,tmp-arr[nx][ny]);
            }
        }
    }
    cout << ans;
}