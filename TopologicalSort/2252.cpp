#include <bits/stdc++.h>

using namespace std;

int N, M;

int idx[32003];
vector<int> edges[32003];

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M;
    int a, b;
    for(int i = 0; i < M; i++){
        cin >> a >> b;
        edges[a].push_back(b);
        idx[b]++;
    }
    queue<int> q, ansq;
    for(int i = 1; i <= N; i++){
        if(!idx[i]){
            q.push(i);
        }
    }
    while(!q.empty()){
        int curp = q.front();
        q.pop();
        ansq.push(curp);
        for(auto next : edges[curp]){
            if(!--idx[next]){
                q.push(next);
            }
        }
    }
    while(!ansq.empty()){
        cout << ansq.front() << " ";
        ansq.pop();
    }
}