#include <bits/stdc++.h>

using namespace std;
using pi = pair<int,int>;
int N;
const int INF=1e9;
vector<vector<int>> adj,cnts;
vector<int> check;
const int MAXPARENT = 18;
int parent[100002][18];
int depth[100002];
void initTree(int x)
{
    for (int next : adj[x])
    {
        if (depth[next] == -1)
        {
            parent[next][0] = x;
            depth[next] = depth[x] + 1;
            initTree(next);
        }
    }
}

int lca(int a, int b)
{
    if (depth[a] < depth[b])
        swap(a, b);
    int diff = depth[a] - depth[b];

    //getting rid of depth diff
    for (int j = 0; diff; j++)
    {
        if (diff % 2)
            a = parent[a][j];
        diff /= 2;
    }

    if (a != b)
    {
        for (int j = MAXPARENT - 1; j >= 0; j--)
        {
            if (parent[a][j] != -1 && parent[a][j] != parent[b][j])
            {
                a = parent[a][j];
                b = parent[b][j];
            }
        }
        a = parent[a][0];
    }
    return a;
}
int checkall(){
    int ret = INF;
    for(int k = 0; k < check.size(); k++){
        int c = check[k];
        for(int i = 0; i < cnts[c].size(); i++){
            for(int j = i+1; j < cnts[c].size(); j++){
                int a=cnts[c][i],b=cnts[c][j];
                ret=min(ret,depth[a]+depth[b]-2*depth[lca(a,b)]);
            }
        }
    }
    return ret;
}

int bfs(int sx){
    queue<int> q;
    vector<pi> dist(N+1,{INF,0});
    for(auto a : cnts[sx]){
        q.push(a);
        dist[a]={0,a};
    }
    int ret = INF;
    bool found=0;
    while(!q.empty()){
        int cx= q.front(),cc=dist[cx].first,cs=dist[cx].second;
        q.pop();
        for(auto nx : adj[cx]){
            if(dist[nx].first!=INF){
                if(dist[nx].second==cs)continue;
                else{
                    found=1;
                    ret=min(ret,cc+dist[nx].first+1);
                    continue;
                }
            }
            if(!found){
            q.push(nx);
            dist[nx]={cc+1,cs};
            }
        }
    }
    return ret;
}

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    int sqn = sqrt(N),cnt=0;
    cnts=vector<vector<int>>(N+1,vector<int>());
    
    for(int i = 0; i < N; i++){
        int a;
        cin >> a;
        cnts[a].push_back(i+1);
    }
    for(int i = 1; i <= N; i++){
        if(cnts[i].size()>1){
            cnt+=cnts[i].size();
            check.push_back(i);
        }
    }
    
    adj=vector<vector<int>>(N+1,vector<int>());
    for(int i = 0; i < N-1; i++){
        int a,b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    
    //cout << "INIT " << endl;
    if((long long)check.size()*N<=1e8){
        int ans = INF;
        //cout << "AHOY" << endl;
        for(auto nxt : check){
            ans=min(ans,bfs(nxt));
        }
        cout << ans;
    }
    else{
        fill(depth, depth + N + 1, -1);
        memset(parent, -1, sizeof(parent));
        depth[1] = 0;
        initTree(1);
        //1 is the root
        for (int j = 0; j < MAXPARENT - 1; j++)
        {
            for (int i = 2; i <= N; i++)
            {
                if (parent[i][j] != -1)
                {
                    parent[i][j + 1] = parent[parent[i][j]][j];
                }
            }
        }
        //cout << "AHA" << endl;
        cout << checkall();
    }
}