#include <bits/stdc++.h>
using namespace std;
int N,M;
vector<int> adj[101010];
int indeg[101010];
int dp[2][101010];
const int INF = 1e9;

int dfs(int cx, int prt, bool flip){
    int& ret = dp[flip][cx];
    if(ret!=-1)return ret;
    ret=INF;
    vector<int> entries;
    for(int nx : adj[cx]){
        if(nx==prt)continue;
        entries.push_back(dfs(nx,cx,!flip));
    }
    sort(entries.begin(),entries.end());
    if(flip){
        ret=entries[0];
    } else {
        for(int i = 0; i < entries.size(); i++){
            ret=min(ret,entries[i]+
            (int)(entries.end()-lower_bound(entries.begin(),entries.end(),entries[i]+1)));
        }
    }
    return ret;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>N>>M;
    memset(dp,-1,sizeof(dp));
    for(int i = 0; i < M ;i++){
        int a,b;cin>>a>>b;
        adj[a].push_back(b);
        indeg[b]++;
    }
    dp[0][N]=0,dp[1][N]=INF;
    vector<int> starts;
    int ans=INF;
    for(int i = 1; i<=N; i++){
        if(!indeg[i])starts.push_back(i);
    }
    for(int x : starts){
        ans=min(ans,dfs(x,0,0));
        //cout << ans << endl;
    }
    cout << (ans==INF?-1:ans) << '\n';
}