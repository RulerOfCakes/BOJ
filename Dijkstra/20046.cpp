#include <bits/stdc++.h>

using namespace std;
using pi = pair<int, int>;
int N, M;
int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};
int arr[1002][1002];
int visited[1002][1002];


void bfs(){
    priority_queue<pair<int, pi>> q;
    if(arr[1][1] == -1)return;
    q.push({-arr[1][1], {1, 1}});
    
    while(!q.empty()){
        int cv = -q.top().first, cx = q.top().second.first, cy = q.top().second.second;
        q.pop();
        if(visited[cx][cy]!=-1)continue;
        visited[cx][cy] = cv;
        if(cx == N && cy == M)break;
        

        for(int i = 0; i < 4; i++){
            int nx = cx+dx[i], ny = cy+dy[i], nv = cv+arr[nx][ny];
            if(nx<1||nx>N||ny<1||ny>M)continue;
            if(arr[nx][ny] == -1)continue;
            if(visited[nx][ny]!=-1)continue;
            q.push({-nv, {nx, ny}});
            
        }
    }
}


int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M;
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= M; j++){
            cin >> arr[i][j];
        }
    }
    memset(visited, -1, sizeof(visited));
    bfs();
    cout << visited[N][M];
}