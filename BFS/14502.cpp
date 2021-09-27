#include <bits/stdc++.h>

using namespace std;
using pi = pair<int,int>;
int N, M;
int arr[10][10];
int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};
int eempty=0;
vector<pi> virus;

int bfs(){
    vector<vector<int>> visited(10,vector<int>(10,0));
    queue<pi> q;
    int ret = 0;
    for(pi p : virus){
        q.push(p);
        visited[p.first][p.second]=1;
    }
    while(!q.empty()){
        int cx, cy;
        tie(cx,cy)=q.front();
        q.pop();
        ret++;
        for(int i = 0; i < 4; i++){
            int nx = dx[i]+cx,ny = dy[i]+cy;
            if(nx<0||nx>=N||ny<0||ny>=M)continue;
            if(visited[nx][ny]||arr[nx][ny])continue;

            visited[nx][ny]=1;
            q.push({nx,ny});
        }
    }
    return ret;
}

int sol(){
    int ret=0;
    for(int i = 0; i < N*M; i++){
        int x1=i/M,y1=i%M;
        if(arr[x1][y1])continue;
        for(int j = i+1; j < N*M; j++){
            int x2=j/M,y2=j%M;
            if(arr[x2][y2])continue;
            for(int k = j+1; k < N*M; k++){
                int x3=k/M,y3=k%M;
                if(arr[x3][y3])continue;
                arr[x1][y1]=1;
                arr[x2][y2]=1;
                arr[x3][y3]=1;
                ret=max(ret,eempty-3-bfs());
                arr[x1][y1]=0;
                arr[x2][y2]=0;
                arr[x3][y3]=0;
            }
        }
    }
    return ret;
}

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M;
    for(int i =0 ; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> arr[i][j];
            if(arr[i][j]==2){
                virus.push_back({i,j});
            }
            if(arr[i][j]!=1)eempty++;
        }
    }
    cout << sol();
}