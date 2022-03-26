#include <bits/stdc++.h>
using namespace std;
using pi = pair<int,int>;
int N,M,K;
const int INF = 1e9;
int dstra(int cx, const vector<vector<pair<int,pi>>>& adj){
    int ret=INF;
    queue<pair<pi, int>> pq;
    pq.push({{0,0},cx});
    vector<vector<int>> dp(102,vector<int>(10101,INF));
    dp[cx][0]=0;
    while(!pq.empty()){
        int cc=pq.front().first.first,cd=pq.front().first.second,cx=pq.front().second;
        pq.pop();
        if(dp[cx][cd]<cc)continue;
        if(cx==N)continue;
        for(const auto& np : adj[cx]){
            int nx=np.first,nc=np.second.first,nd=np.second.second;
            if(cd+nd>M||dp[nx][cd+nd]<=cc+nc)continue;
            dp[nx][cd+nd]=cc+nc;
            pq.push({{cc+nc,cd+nd},nx});
        }
    }
    for(int i = 0; i <= M; i++){
        ret=min(ret,dp[N][i]);
    }
    if(ret==INF)ret=-1;
    return ret;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    int T;cin>>T;
    while(T--){    
        cin>>N>>M>>K;
        vector<vector<pair<int,pi>>> adj(N+1,vector<pair<int,pi>>());
        for(int i = 0; i < K; i++){
            int u,v,c,d;
            cin>>u>>v>>c>>d;
            adj[u].push_back({v,{d,c}});
            //adj[v].push_back({u,{d,c}});
        }
        int res=dstra(1,adj);
        cout << (res!=-1?to_string(res):"Poor KCM") << '\n';
    }
}