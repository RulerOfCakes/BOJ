#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using ll = long long;
int normN;

class DinicFlow{
    public:
    int N, source, sink;

    vector<vector<int>> adj;
    vector<vector<int>> cp,flw;
    vector<int> level,work;
    queue<int> bq;

    DinicFlow():N(0),source(0),sink(0),adj(),level(),bq(){}
    DinicFlow(int N, int source, int sink):N(N),source(source),sink(sink),adj(N),level(N),work(N),cp(N,vector<int>(N)),flw(N,vector<int>(N)){}
    
    void add_edge(int from, int to, int cap){
        adj[from].push_back(to);
        cp[from][to]=cap;
    }

    bool levelling(){
        level=vector<int>(N,-1);
        level[source]=0;
        bq.push(source);
        while(!bq.empty()){
            int now = bq.front();
            bq.pop();
            for(const auto nxt:adj[now]){
                if(level[nxt]==-1&&cp[now][nxt]-flw[now][nxt]>0){
                    level[nxt]=level[now]+1;
                    bq.push(nxt);
                }
            }
        }
        return level[sink]!=-1;
    }

    int dfs(int now, int mf){
        if(now==sink)return mf;
        for(int &i = work[now]; i < adj[now].size(); i++){
            int nxt = adj[now][i];
            if(level[nxt]==level[now]+1&&cp[now][nxt]-flw[now][nxt]>0){
                int flow=dfs(nxt,min(mf,cp[now][nxt]-flw[now][nxt]));
                if(flow>0){
                    flw[now][nxt]+=flow;
                    flw[nxt][now]-=flow;
                    return flow;
                }
            }
        }
        return 0;
    }

    int max_flow(){
        int ret=0;
        while(levelling()){
            work=vector<int>(N,0);
            int flow=0;
            while(flow=dfs(source,INT_MAX))
                ret+=flow;
        }
        return ret;
    }
    void check(){
        queue<int> q;
        q.push(source);
        vector<int>chk(N);
        chk[source]=1;
        while(!q.empty()){
            int now = q.front(); q.pop();
            for(auto nxt : adj[now]){
                if(!chk[nxt]&&cp[now][nxt]-flw[now][nxt] > 0){
                    chk[nxt]=1;
                    q.push(nxt);
                }
            }
        }
        vector<int> A,B;
        for(int i = 1; i <= normN; i++){
            if(chk[i])A.push_back(i);
            else B.push_back(i);
        }
        for(int i : A)cout << i << ' ';
        cout << '\n';
        for(int i : B)cout << i << ' ';
        cout << '\n';//removing this causes WA
    }
};
const int INF = 1e9+7;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, M;

    cin >> N;
    normN=N;

    int source = 0, sink = N + 2;
    DinicFlow df(N + 3, source, sink);
    for(int i = 0; i < N; i++){
        int a;
        cin >> a;
        if(a==1){
            df.add_edge(source,i+1,INF);
        }
        else if(a==2){
            df.add_edge(i+1,sink,INF);
        }
    }
    for (int i = 1; i <= N; i++)
    {
        for(int j = 1; j <= N; j++){
            int a;
            cin >> a;
            if(i==j)continue;
            df.add_edge(i,j,a);
        }
    }
    
    
    cout << df.max_flow() << '\n';
    df.check();
}