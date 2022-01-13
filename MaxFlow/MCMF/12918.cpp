#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using ll = long long;
template <typename T>
class MCMF
{
public:
    struct Edge{
        int from,to;
        T cap,cost;
        int revid;
        Edge(int from, int to, T cap, T cost, int revid):from(from),to(to),cap(cap),cost(cost),revid(revid){}
    };
    int N, source, sink;
    vector<vector<Edge>> adj;
    vector<bool> inQ;
    vector<T> dist;
    vector<int> chk, work;
    MCMF(int N, int source, int sink) : N(N), source(source), sink(sink), adj(N), dist(N), inQ(N), chk(N), work(N) {}

    void add_edge(int from, int to, T cap, T cost){
        Edge e(from,to,cap,cost,adj[to].size());
        Edge e_reverse(to,from,0,-cost,adj[from].size());
        adj[from].push_back(e);
        adj[to].push_back(e_reverse);
    }

    bool SPFA(){
        fill(dist.begin(),dist.end(),1e9);
        fill(inQ.begin(),inQ.end(),0);
        queue<int> q;
        q.push(source);
        inQ[source]=1;
        dist[source]=0;
        while(!q.empty()){
            int nx=q.front();
            q.pop();
            inQ[nx]=0;
            for(auto e : adj[nx]){
                if(e.cap&&dist[e.to]>dist[nx]+e.cost){
                    dist[e.to]=dist[nx]+e.cost;
                    if(!inQ[e.to])inQ[e.to]=1,q.push(e.to);
                }
            }
        }
        return dist[sink]<1e9;
    }

    T dfs(int cx, T mf)
    {
        chk[cx]=1;
        if (cx == sink)
            return mf;

        for (int& i = work[cx]; i<adj[cx].size(); i++)
        {
            auto& p = adj[cx][i];
            if(!chk[p.to]&&dist[p.to]==dist[cx]+p.cost && p.cap){
                T flow = dfs(p.to, min(mf,p.cap));
                if(flow){
                    p.cap-=flow;
                    adj[p.to][p.revid].cap+=flow;
                    return flow;
                }
            }
        }
        return 0;
    }

    pair<T,T> run(){
        T cost=0,flow=0;
        while(SPFA()){
            fill(chk.begin(),chk.end(),0);
            fill(work.begin(),work.end(),0);
            T nx=0;
            while(nx=dfs(source,1e9)){
                cost+=dist[sink]*nx;
                flow+=nx;
                fill(chk.begin(),chk.end(),0);
            }
        }
        return make_pair(cost,flow);
    }
};

double dist(pi p1, pi p2){
    double x,y,c,d;
    tie(x,y)=p1;tie(c,d)=p2;
    return sqrt((x-c)*(x-c)+(y-d)*(y-d));
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N, M;

    cin >> N;
    vector<pi> v(2*N+2);
    for(int i = 1; i <= N; i++)cin >> v[i].first >> v[i].second;

    int source = 202, sink = 203;
    MCMF<double> mf(205, source, sink);
    // parallel points on the y axis for each point
    for(int i = N; i; i--){
        v[i<<1]=v[i<<1|1]=v[i];
        v[i<<1|1].first*=-1;
        //connect source to all original points
        mf.add_edge(source,i<<1,1,0);
        //connect sink to all parallel (fake) points
        mf.add_edge(i<<1|1,sink,1,0);
    }
    for (int i = 1; i <= N; i++)
    {
        //og point = i
        for(int j =1; j <= N; j++){
            //parallel point = j
            mf.add_edge(i<<1,j<<1|1,1,dist(v[i<<1],v[j<<1|1])/2);
        }
    }
    pair<double,double> p = mf.run();
    cout << fixed << setprecision(3) << p.first;
}