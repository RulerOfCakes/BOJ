#include <bits/stdc++.h>

using namespace std;

int N;
int dist[10003];
int ttime[10003];
int idx[10003];
vector<int> edges[10003];

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    for(int i = 0; i < N; i++){
        cin >> ttime[i+1] >> idx[i+1];
        for(int j = 0; j < idx[i+1]; j++){
            int a;
            cin >> a;
            edges[a].push_back(i+1);
        }
    }
    queue<int> q;
    for(int i = 1; i <= N; i++){
        if(!idx[i]){
            q.push(i);
            dist[i] = ttime[i];
        }
    }
    while(!q.empty()){
        int curp = q.front();
        q.pop();

        for(auto next : edges[curp]){
            dist[next] = max(dist[next], dist[curp] + ttime[next]);
            if(!--idx[next]){
                q.push(next);
            }
        }
    }
    int ans = 0;
    for(int i = 1; i <= N; i++){
        ans = max(ans, dist[i]);
    }

    cout << ans;
}