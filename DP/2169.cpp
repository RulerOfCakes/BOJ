#include <bits/stdc++.h>

using namespace std;
using ll = long long;
int N, M;
int arr[1002][1002];
int dp[1002][1002][3];//down, right, left
int visited[1002][1002];

int dx[] = {1, 0, 0};
int dy[] = {0, 1, -1};

const int INF = -1e9;

int sol(int x, int y, int p){
    if(x==N-1&&y==M-1)return arr[x][y];

    int& ret = dp[x][y][p];
    if(ret!=INF)return ret;
    //down, right, left
    for(int i = 0; i < 3; i++){
        int nx = x + dx[i], ny = y + dy[i];
        if(nx<0||nx>=N||ny<0||ny>=M)continue;
        if(visited[nx][ny])continue;
        visited[nx][ny]=1;
        ret=max(ret, sol(nx, ny, i) + arr[x][y]);
        visited[nx][ny]=0;
    }
    return ret;
}


int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> arr[i][j];
            dp[i][j][0]=dp[i][j][1]=dp[i][j][2]=INF;
        }
    }

    visited[0][0]=1;
    cout << sol(0, 0, 0);
}