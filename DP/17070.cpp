#include <bits/stdc++.h>
using namespace std;
int N,M;
int arr[17][17];
int dp[17][17][3];
int dx[]={1,0,1};
int dy[]={0,1,1};
//x and y are endpoint coordinates
int sol(int x, int y, int rot){
    if(x==N-1&&y==N-1)return 1;
    int& ret=dp[x][y][rot];
    if(ret!=-1)return ret;
    ret=0;
    for(int i=0;i<3;i++){
        if((rot==0||rot==1)&&i+rot==1)continue;
        int nx=dx[i]+x,ny=dy[i]+y;
        if(nx>=N||ny>=N||arr[nx][ny])continue;
        if(i==2&&(arr[x][y+1]||arr[x+1][y]))continue;
        ret+=sol(nx,ny,i);
    }
    return ret;
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>N;
    memset(dp,-1,sizeof(dp));
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin>>arr[i][j];
        }
    }
    cout << sol(0,1,1);
}