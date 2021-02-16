#include <bits/stdc++.h>

using namespace std;

int N, M, startp, endp;
int dist[10003];
bool visitt[10003];
int idx[10003];
vector<pair<int, int>> edges[10003];
vector<pair<int, int>> redges[10003];

int backtrack(){
    stack<int> s;
    int ret = 0;
    s.push(endp);
    while(!s.empty()){
        int cur = s.top();
        s.pop();
        if(visitt[cur])continue;
        visitt[cur] = 1;
        for(auto i : redges[cur]){
            int next = i.first, val = i.second;
            if(dist[cur] == dist[next] + val){
                s.push(next);
                ret++;
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
    int a, b, c;
    for(int i = 1; i <= M; i++){
        cin >> a >> b >> c;
        idx[b]++;
        edges[a].push_back({b, c});
        redges[b].push_back({a, c});
    }
    cin >> startp >> endp;
    queue<int> q;
    for(int i = 1; i <= N; i++){
        if(!idx[i]){
            q.push(i);
        }
    }
    while(!q.empty()){
        int curp = q.front();
        q.pop();

        for(auto i : edges[curp]){
            int next = i.first, val = i.second;
            dist[next] = max(dist[next], dist[curp] + val);
            if(!--idx[next]){
                q.push(next);
            }
        }
    }
    int ans = 0;
    for(int i = 1; i <= N; i++){
        ans = max(ans, dist[i]);
    }

    cout << ans << '\n';

    cout << backtrack();
}