#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pi = pair<int,int>;
const int INF = 1e9;
int T,N,M;
int s,g,h;
vector<vector<pi>> adj;
vector<int> dist;
vector<bool>ok;

void dijkstra(){
    priority_queue<pi> pq;
    pq.push({0,s});
    dist[s]=0;
    while(!pq.empty()){
        int cx,cc;
        tie(cc,cx)=pq.top();
        cc=-cc;
        pq.pop();
        if(dist[cx]<cc)continue;
        for(auto np : adj[cx]){
            int nx,nc;
            tie(nx,nc)=np;
            if(dist[nx]<=cc+nc)continue;
            dist[nx]=cc+nc;
            pq.push({-(cc+nc),nx});
        }
    }
}


bool backtrack(int sx){
    if(dist[sx]==INF)return false;
    queue<int> q;
    vector<bool> inQ(N+1,0);
    q.push(sx);
    while(!q.empty()){
        int cx = q.front();
        q.pop();
        inQ[cx]=false;
        for(auto np : adj[cx]){
            int nx,nc;
            tie(nx,nc)=np;
            if(inQ[nx])continue;
            if(dist[nx]==dist[cx]-nc){
                q.push(nx);
                inQ[nx]=1;
                if((nx==g && cx == h)||(cx==g&&nx==h))return true;
            }
        }
    }
    return false;
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    cin >> T;
    while(T--){
        int t;
        cin >> N >> M >> t;
        adj=vector<vector<pi>>(N+1,vector<pi>());
        ok=vector<bool>(N+1);
        dist=vector<int>(N+1,INF);
        vector<int> cv;
        cin >> s >> g >> h;
        for(int i = 0; i < M; i++){
            int a,b,c;
            cin >> a >> b >> c;
            adj[a].push_back({b,c});
            adj[b].push_back({a,c});
        }
        dijkstra();
        
        
        for(int i = 0; i < t; i++){
            int a;
            cin >> a;
            cv.push_back(a);
            if(backtrack(a))ok[a]=1;
        }
        sort(cv.begin(),cv.end());
        for(int cx : cv){
            if(ok[cx]){
                cout << cx << ' ';
            }
        }
        cout << '\n';
    }
}