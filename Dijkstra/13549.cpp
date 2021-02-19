#include <bits/stdc++.h>

using namespace std;

int N, K;
int visited[100002];

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> K;
    if(N == K){
        cout << 0;
        return 0;
    }
    memset(visited, -1, sizeof(visited));
    priority_queue<pair<int, int>> q;
    q.push({0, N});

    while(!q.empty()){
        int cur = q.top().second, val = -q.top().first;
        q.pop();
        if(visited[cur] != -1)continue;
        visited[cur] = val;
        for(int next : {cur*2, cur-1, cur+1}){
            if(next < 0 || next > 100000)continue;
            if(visited[next] != -1)continue;
            if(next == cur*2){
                q.push({-val, next});
            }
            else{
                q.push({-(val+1), next});
            }
        }
    }
    cout << visited[K];
}