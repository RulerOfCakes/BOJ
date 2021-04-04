#include <bits/stdc++.h>

using namespace std;
using pi = pair<int, int>;
int N, M;
char arr[52][52];
int visited[52][52][1<<7+1];
int ans = -1;
int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};
//CLOSE THE OPENED DOORS YOU FOOL
void bfs(int a, int b){
    queue<pair<pi, int>> q;
    q.push({{a, b}, 0});
    visited[a][b][0]=1;
    while(!q.empty()){
        int cx = q.front().first.first, cy = q.front().first.second,
            keys = q.front().second;
        int cur = visited[cx][cy][keys];
        q.pop();
        
        //cout << cur << '\n';
        for(int i = 0; i < 4; i++){
            int nx = cx + dx[i], ny = cy + dy[i];
            if(nx<0||nx>=N||ny<0||ny>=M)continue;
            if(arr[nx][ny] == '#')continue;
            if(visited[nx][ny][keys])continue;
            visited[nx][ny][keys]=cur+1;
            char c = arr[nx][ny];
            if(c <= 'F' && c >= 'A'){
                if(!(keys&(1<<(c-'A')))){
                    visited[nx][ny][keys] = 0;
                    continue;
                }
                
                q.push({{nx, ny}, keys});
            }
            else if(c >= 'a' && c <= 'f'){
                if(keys&(1<<(c-'a'))){
                    q.push({{nx, ny}, keys});
                }
                else{
                    q.push({{nx, ny}, keys+(1<<(c-'a'))});
                    visited[nx][ny][keys+(1<<(c-'a'))] = cur+1;
                }
            }
            else if(c == '1'){
                ans = cur;
                return;
            }
            else{
                q.push({{nx, ny}, keys});
            }
        }
    }
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M;
    int a, b;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            cin >> arr[i][j];
            if(arr[i][j] == '0'){
                a=i;
                b=j;
            }
        }
    }
    bfs(a, b);
    
    cout << ans;
}