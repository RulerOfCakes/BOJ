#include <bits/stdc++.h>

using namespace std;

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
int M, N;
char tmap[52][52];
bool verify(int n, int m){
    if(n > N || m > M)return false;
    if(n <= 0 || m <= 0)return false;
    if(tmap[n][m] == 'W')return false;
    else return true;
}

int bfs(int sx, int sy){
    queue<pair<int, int>> q;
    vector<vector<int>> v(51, vector<int>(51, -1));
    q.push({sx, sy});
    v[sx][sy] = 0;
    int ret = 0;
    while(!q.empty()){
        int curx = q.front().first, cury = q.front().second;
        q.pop();

        for(int i = 0; i < 4; i++){
            int nextx = curx + dx[i], nexty = cury + dy[i];
            if(!verify(nextx, nexty))continue;
            if(v[nextx][nexty] != -1)continue;
            else{
                v[nextx][nexty] = v[curx][cury] + 1;
                ret = max(ret, v[nextx][nexty]);
                q.push({nextx, nexty});
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
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> tmap[i+1][j+1];
        }
    }
    int ans = 0;
    for(int i = 1; i <= N; i++){
        for(int j = 1; j <= M; j++){
            if(!verify(i, j))continue;
            ans = max(ans, bfs(i, j));
        }
    }
    cout << ans;
    
}