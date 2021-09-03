#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using ll = long long;
const ll INF = 1e12+7;
const int MAX_V = 502;
int N, M;

ll dist[502],cost[502];

vector<pi> adj[MAX_V];

bool SPFA(int start){
    queue<int> q;
    q.push(start);
    
    vector<int> cycles(MAX_V,0);
    vector<bool> inQ(MAX_V);

    dist[start]=0;
    inQ[start]=1;
    cycles[start]++;
    while(!q.empty()){
        int cx=q.front();
        q.pop();
        inQ[cx]=false;
        for(pi np : adj[cx]){
            int nx=np.first,cost=np.second;

            if(dist[nx]>dist[cx]+cost){
                dist[nx]=dist[cx]+cost;
                if(!inQ[nx]){
                    cycles[nx]++;
                    if(cycles[nx]>=N){
                        return 1;
                    }
                    q.push(nx);
                    inQ[nx]=1;
                }
            }
        }

    }
    return 0;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> N >> M;

    for(int i = 0; i < M; i++){
        int a,b,c;
        cin >> a >> b >> c;
        adj[a].push_back({b,c});
    }
    fill(dist,dist+MAX_V,INF);
    if(SPFA(1)){
        cout << -1;
    } else {
        for(int i = 2; i <= N; i++){
            cout << (dist[i]!=INF?dist[i]:-1) << '\n';
        }
    }

}