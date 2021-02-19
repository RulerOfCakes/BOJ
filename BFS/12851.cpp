#include <bits/stdc++.h>

using namespace std;

int N, K;
int visited[100002];
int visitnum[100002];

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> K;
    memset(visited, -1, sizeof(visited));
    queue<pair<int, int>> q;
    q.push({0, N});
    visited[N] = 0;
    visitnum[N] = 1;
    while(!q.empty()){
        int cur = q.front().second, val = q.front().first + 1;
        q.pop();
        
        for(int next : {cur-1, cur+1, cur*2}){
            if(next < 0 || next > 100000)continue;
            if(visited[next] < val && visited[next] != -1)continue;
            visited[next] = val;
            visitnum[next]++;
            q.push({val, next});
        }
    }
    cout << visited[K] << '\n';
    cout << visitnum[K];
}