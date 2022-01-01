#include <bits/stdc++.h>

using namespace std;
using pi = pair<int,int>;
int N;
bool visited[102][102][2];
char arr[102][102];
int dx[]={0,0,-1,1},dy[]={1,-1,0,0};
int ans[2]={0,0};
char code(char c,bool blind){
    if(blind&&c=='G')return 'R';
    else return c;
}
void bfs(int sx, int sy, bool blind){
    queue<pi> q;
    q.push({sx,sy});
    char par=code(arr[sx][sy],blind);
    visited[sx][sy][blind]=1;
    while(!q.empty()){
        auto [cx,cy]=q.front();
        q.pop();
        for(int i = 0; i < 4; i++){
            int nx=dx[i]+cx,ny=dy[i]+cy;
            if(nx<0||nx>=N||ny<0||ny>=N)continue;
            if(visited[nx][ny][blind]||code(arr[nx][ny],blind)!=par)continue;
            q.push({nx,ny});
            visited[nx][ny][blind]=1;
        }
    }
    ans[blind]++;
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cin>>arr[i][j];
        }
    }
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            for(int k = 0; k < 2; k++){
                if(!visited[i][j][k])bfs(i,j,k);
            }
        }
    }
    cout << ans[0] << ' ' << ans[1];
}