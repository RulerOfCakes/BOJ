#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;

int N;
const int INF = 2e9+1;

class Edge{
    public:
    int from,to,cap,flow;
    Edge *reverse;
    Edge():from(0),to(0),cap(0),flow(0),reverse(nullptr){}
    Edge(const Edge& e):from(e.from),to(e.to),cap(e.cap),flow(e.flow),reverse(e.reverse){}
    Edge(int from, int to, int cap):from(from),to(to),cap(cap),flow(0),reverse(nullptr){}

};
vector<vector<Edge*>> adj;
vector<bool> visited;
int source, sink;
void add_edge(int from, int to, int cap){
    Edge* e = new Edge(from,to,cap);
    Edge* e_reverse = new Edge(to,from,0);
    e->reverse=e_reverse;
    e_reverse->reverse=e;
    adj[from].push_back(e);
    adj[to].push_back(e_reverse);
}

int dfs(int cx, int mf){
    if(cx==sink)return mf;
    if(visited[cx])return 0;
    visited[cx]=1;
    for(Edge* e : adj[cx]){
        if(e->cap-e->flow>0){
            int flow=dfs(e->to,min(mf,e->cap-e->flow));
            if(flow>0){
                e->flow+=flow;
                e->reverse->flow-=flow;
                return flow;
            }
        }
    }
    return 0;
}

int max_flow(){
    int ret=0;
    while(true){
        int flow=dfs(source,INT_MAX);
        fill(visited.begin(),visited.end(),false);
        if(flow==0)break;
        ret+=flow;
        
    }
    return ret;
}
int A[51],B[51],C[51];
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> N;
    for(int i = 1; i <= N; i++){
        cin >> A[i] >> B[i] >> C[i];
    }
    adj=vector<vector<Edge*>>(102);
    visited=vector<bool>(102,0);
    source=0;sink=101;
    for (int i = 1; i <= N; i++)
    {
        add_edge(source,i,2);
        add_edge(i+50,sink,1);
        for(int j = 1; j <= N; j++){
            if(i==j)continue;
            if(A[i]>=A[j]&&B[i]>=B[j]&&C[i]>=C[j]){
                if(A[i]==A[j]&&B[i]==B[j]&&C[i]==C[j]){
                    if(i<j)add_edge(i,j+50,1);
                }
                else{
                    add_edge(i,j+50,1);
                }
            }
        }
    }
    cout << N-max_flow();
}