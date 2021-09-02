#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;

const int INF = 1e9+7;
struct Edge
{
    int from, to, cap, flow;
    Edge *reverse;
    Edge() : from(0), to(0), cap(0), flow(0), reverse(nullptr) {}
    Edge(const Edge &e) : from(e.from), to(e.to), cap(e.cap), flow(e.flow), reverse(e.reverse) {}
    Edge(int from, int to, int cap) : from(from), to(to), cap(cap), flow(0), reverse(nullptr) {}
};
class DinicFlow
{
public:
    int N, source, sink;
    vector<vector<Edge *>> adj;
    vector<int> level;
    queue<int> bq;
    vector<int> work;
    DinicFlow() : N(0), source(0), sink(0), adj(), level(), bq(), work() {}
    DinicFlow(const DinicFlow &df) : N(df.N), source(df.source), sink(df.sink), adj(df.adj), level(df.level), bq(df.bq), work(df.work) {}
    DinicFlow(int N, int source, int sink) : N(N), source(source), sink(sink), adj(N), level(N), bq(), work(N) {}

    void add_edge(int from, int to, int cap)
    {
        Edge *e = new Edge(from, to, cap);
        Edge *e_reverse = new Edge(to, from, 0);
        e->reverse = e_reverse;
        e_reverse->reverse = e;
        adj[from].push_back(e);
        adj[to].push_back(e_reverse);
    }

    bool levelling()
    {
        level=vector<int>(N,-1);
        level[source] = 0;
        bq=queue<int>();
        bq.push(source);
        while (!bq.empty())
        {
            int now = bq.front();
            bq.pop();
            for (auto e : adj[now])
            {
                if (level[e->to] == -1 && e->cap > 0)
                {
                    level[e->to] = level[now] + 1;
                    bq.push(e->to);
                }
            }
        }
        return (level[sink] != -1);
    }

    int dfs(int cx, int mf)
    {
        if (cx == sink)
        {
            return mf;
        };

        for(int &i = work[cx]; i < adj[cx].size(); i++)
        {
            auto e=adj[cx][i];
            if (level[e->to] == level[cx] + 1 && e->cap > 0)
            {
                int flow = dfs(e->to, min(mf, e->cap));
                if (flow)
                {
                    e->cap-=flow;
                    e->reverse->flow+=flow;
                    e->flow += flow;
                    e->reverse->flow -= flow;
                    return flow;
                }
            }
        }
        return 0;
    }

    int max_flow()
    {
        int ret = 0;
        while (levelling())
        {
            work=vector<int>(N);
            int flow=0;
            while(flow=dfs(source,INF))
                ret += flow;
        }
        return ret;
    }

    void print(int k){
        while (k--) {
			cout << source/2 << ' ';
			work=vector<int>(N);
			for (int now = source; now != sink;) {
				for(int &i = work[now]; i<adj[now].size(); i++){
					auto e = adj[now][i];
					if (e->flow > 0) {
						now = e->to;
						e->flow = 0;
						if (e->to %2==0)
							cout << e->to/2 << ' ';
						break;
					}
				}
			}
			cout << '\n';
		}
    }
    ~DinicFlow(){
        for(auto &i : adj){
            for(auto &e : i){
                delete e;
            }
        }
    }
};

int main()
{
    int K, N;
    ios::sync_with_stdio(false);
    cin.tie(0);
    int counter = 1;
    while (true)
    {
        cin >> K >> N;
        if (K == 0 && N == 0)
            break;
        
        cin.ignore();
        int source = 1*2+1, sink = 2*2;
        DinicFlow df(2 * (N + 1), source, sink);
       
        for (int i = 1; i <= N; i++)
        {
            df.add_edge(i*2,i*2+1, 1);
        }
        
        for (int i = 1; i <= N; i++)
        {
            string s;
            getline(cin, s);
            istringstream iss(s);
            do{
                string ts;
                iss >> ts;
                if(ts=="")break;
                int u = stoi(ts);
                df.add_edge(i*2+1,u*2,1);
            }while(iss);
        }

        cout << "Case " << counter++ << ":\n";
        //cout << df.max_flow() << '\n';
        if (df.max_flow() >= K)
        {
            df.print(K);
            cout << '\n';
        }
        else
        {
            cout << "Impossible\n\n";
        }
        
    }
    

}