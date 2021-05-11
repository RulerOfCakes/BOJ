#include <bits/stdc++.h>

using namespace std;

int N, M ,K;
vector<vector<int>> friends;
vector<int> candies;
vector<int> visited;
vector<pair<int, int>> eq;

void bfs(int a){
    queue<int> q;
    pair<int, int> pa = {0, 0};
    q.push(a);
    visited[a]=1;
    while(!q.empty()){
        int cur = q.front();
        q.pop();
        pa.first += candies[cur];
        pa.second++;
        
        for(int c : friends[cur]){
            if(visited[c])continue;
            visited[c]=1;
            q.push(c);
        }
    }
    eq.push_back(pa);
}

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N>>M>>K;
    friends = vector<vector<int>>(N, vector<int>());
    candies = vector<int>(N, 0);
    visited = vector<int>(N, 0);
    for(int i = 0; i < N; i++){
        cin >> candies[i];
    }
    //01kn
    for(int i = 0; i < M; i++){
        int a, b;
        cin >> a >> b;
        friends[a-1].push_back(b-1);
        friends[b-1].push_back(a-1);
    }
    for(int i = 0; i < N; i++){
        if(!visited[i])bfs(i);
    }
    int ans=0;
    vector<vector<int>> dp(eq.size()+1, vector<int>(K+1, 0));
    for(int i=0;i<eq.size();i++){
        for(int j=1;j<K;j++){
            if(eq[i].second<=j){
                dp[i+1][j]=max(dp[i][j], dp[i][j-eq[i].second] + eq[i].first);
            }
            else{
                dp[i+1][j]=dp[i][j];
            }
            //ans =max(ans, dp[i+1][j]);
        }
    }
    for(int i= 0; i < K; i++){
        ans = max(ans, dp[eq.size()][i]);
    }
    cout << ans;
}