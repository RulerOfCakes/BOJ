#include <bits/stdc++.h>

using namespace std;

int N;
int dist[503];
int ttime[503];
int idx[503];
vector<int> edges[503];

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    for(int i = 0; i < N; i++){
        int a;
        cin >> ttime[i+1] >> a;
        while(a!=-1){
            edges[a].push_back(i+1);
            idx[i+1]++;
            cin >> a;
        }
    }
    priority_queue<pair<int, int>> q;
    for(int i = 1; i <= N; i++){
        if(!idx[i]){
            q.push({-ttime[i], i});
            dist[i] = ttime[i];
        }
    }
    while(!q.empty()){
        int curp = q.top().second, curx = -q.top().first;
        q.pop();

        for(auto next : edges[curp]){
            dist[next] = max(dist[next], dist[curp] + ttime[next]);
            if(!--idx[next]){
                q.push({-dist[next], next});
            }
        }
    }
    for(int i = 1; i <= N; i++){
        cout << dist[i] << '\n';
    }
}