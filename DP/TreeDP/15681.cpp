#include <bits/stdc++.h>

using namespace std;

int N, R, Q;
int dp[100002];
bool visited[100002];

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> R >> Q;
    vector<int> edges[N+1];
    for(int i = 1; i < N; i++){
        int a, b;
        cin >> a >> b;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    stack<int> s;
    s.push(R);
    while(!s.empty()){
        int cur = s.top();
        
        if(visited[cur]){
            
            for(auto a: edges[cur]){
                dp[cur] += dp[a];
            }
            dp[cur] += edges[cur].size();
            s.pop();
            continue;
        }
        visited[cur] = 1;
        
        for(auto a : edges[cur]){
            if(visited[a])continue;
            s.push(a);
        }
        
    }
    for(int i = 0; i < Q; i++){
        int a;
        cin >> a;
        cout << dp[a]/2+1 << '\n';
    }
}