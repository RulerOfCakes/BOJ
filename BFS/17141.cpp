#include <bits/stdc++.h>

using namespace std;
using pi = pair<int, int>;
int N, M, ans = -1;
int dx[] = {0, 0, -1, 1};
int dy[] = {1, -1, 0, 0};
int arr[52][52];
bool spread[12];
vector<pi> virus;


void bfs(){
    vector<vector<int>> visited(52, vector<int>(52, 0));
    queue<pi> q;
    for(int i = 0; i < virus.size(); i++){
        if(spread[i]){
            q.push({virus[i].first, virus[i].second});
            visited[virus[i].first][virus[i].second] = 1;
        }
    }
    while(!q.empty()){
        int curx = q.front().first, cury = q.front().second;
        q.pop();
        for(int i = 0; i < 4; i++){
            int nextx = curx + dx[i], nexty = cury + dy[i];
            if(nextx < 1 || nextx > N || nexty < 1 || nexty > N)continue;
            if(visited[nextx][nexty])continue;
            if(arr[nextx][nexty]==1)continue;
            visited[nextx][nexty] = visited[curx][cury]+1;
            q.push({nextx, nexty});
        }
    }
    int tempans = 0;
    for(int  i =1; i <= N; i++){
        for(int j = 1; j <= N; j++){
            if(arr[i][j] == 1)continue;
            if(!visited[i][j]) return;
            tempans = max(tempans, visited[i][j]);
        }
    }
    if(ans != -1){
        ans = min(ans, tempans);
    }
    else{
        ans = tempans;
    }
}

void Backtracking(int s, int cnt){
    if(cnt == M){
        bfs();
        return;
    }
    for(int i = s; i < virus.size(); i++){
        spread[i] = 1;
        Backtracking(i+1, cnt+1);
        spread[i] = 0;
    }
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> arr[i + 1][j + 1];
            if(arr[i+1][j+1]==2){
                virus.push_back({i+1, j+1});
            }
        }
    }
    Backtracking(0, 0);

    if(ans != -1){
        cout << ans-1;
    }
    else{
        cout << ans;
    }
}