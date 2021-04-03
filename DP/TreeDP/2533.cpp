#include <bits/stdc++.h>

using namespace std;

int N;
int dp[1000002][2];
bool visited[1000002];
vector<vector<int>> v;

void dfs(int root){
    if(visited[root])return;
    visited[root]=1;
    // dp[root][0] = 0;
    // dp[root][1] = arr[root];

    for(auto next : v[root]){
        if(visited[next])continue;
        dfs(next);

        dp[root][0] += dp[next][1];

        dp[root][1] += min(dp[next][0], dp[next][1]);
    }
    dp[root][1]++;
}

int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    v = vector<vector<int>>(N+1, vector<int>());
    for(int i = 1; i < N; i++){
        int a, b;
        cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    dfs(1);
    
    cout << min(dp[1][1], dp[1][0]);
}