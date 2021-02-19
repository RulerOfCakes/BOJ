#include <bits/stdc++.h>

using namespace std;

int N, K;
int visited[100002];
int idxs[100002];

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> K;
    if(N == K){
        cout << 0 << '\n' << N;
        return 0;
    }
    memset(visited, -1, sizeof(visited));
    memset(idxs, -1, sizeof(idxs));
    queue<pair<int, int>> q;
    q.push({0, N});
    visited[N] = 0;
    while(!q.empty()){
        int cur = q.front().second, val = q.front().first+ 1;
        q.pop();
        if(visited[K] != -1)break;
        
        for(int next : {cur-1, cur+1, cur*2}){
            if(next < 0 || next > 100000)continue;
            if(visited[next] != -1)continue;
            idxs[next] = cur;
            visited[next] = val;
            q.push({val, next});
        }
    }
    cout << visited[K] << '\n';
    int idx = K;
    stack<int> s;
    s.push(K);
    while(idxs[idx] != -1){
        s.push(idxs[idx]);
        idx = idxs[idx];
    }
    while(!s.empty()){
        cout << s.top() << ' ';
        s.pop();
    }
}