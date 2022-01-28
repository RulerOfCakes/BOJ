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


int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int N,T,F;
    int source = 102, sink = 103;
    MCMF<int> mfmax(105, source, sink),mfmin(105,source,sink);
    cin >> N;
    vector<int> in(N),out(N);
    for(int i = 0; i < N; i++){
        cin>>in[i];
    }
    for(int i = 0; i < N; i++){
        cin>>out[i];
    }
    sort(in.begin(),in.end());sort(out.begin(),out.end());
    cin>>T>>F;
    for(int i = 0; i < N; i++){
        int pos = lower_bound(out.begin(),out.end(),in[i])-out.begin();
        while(pos!=N&&out[pos]==in[i])pos++;
        mfmax.add_edge(source,i,1,0);
        mfmax.add_edge(i+N,sink,1,0);
        mfmin.add_edge(source,i,1,0);
        mfmin.add_edge(i+N,sink,1,0);
        for(int j = pos; j < N; j++){
            int s = out[j]-in[i];
            if(T>s){
                mfmax.add_edge(i,N+j,1,min((T-s)*(T-s),F));
                mfmin.add_edge(i,N+j,1,-min((T-s)*(T-s),F));
            } else {
                mfmax.add_edge(i,N+j,1,0);
                mfmin.add_edge(i,N+j,1,0);
            }
        }
    }

    auto p1 = mfmin.run();
    auto p2 = mfmax.run();
    if(p1.second<N||p2.second<N)cout << -1;
    else
        cout << p2.first << ' ' << -p1.first;
}