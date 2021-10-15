#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pi = pair<int,int>;
using pl = pair<ll,ll>;

int N, M;
int A, B, C;
const int INF = 1e9;
const ll LNF = 1e18;

class segtree
{
public:
    vector<ll> tree;

    int size;

    segtree(int n)
    {
        for (size = 1; size < n; size *= 2)
            ;
        tree.resize(size * 2, LNF);
    }
    void update(int node, ll x)
    {
        int idx = size + node - 1;
        tree[idx] = min(x,tree[idx]);
        idx /= 2;
        while (idx)
        {
            tree[idx] = min(tree[idx * 2], tree[idx * 2 + 1]);
            idx /= 2;
        }
    }

    ll query(int node, int nStart, int nEnd, int rStart, int rEnd)
    {
        if (nEnd < rStart || nStart > rEnd)
            return LNF;
        if (rStart <= nStart && rEnd >= nEnd)
            return tree[node];
        int mid = (nStart + nEnd) / 2;
        return min(query(node * 2, nStart, mid, rStart, rEnd), query(node * 2 + 1, mid + 1, nEnd, rStart, rEnd));
    }
};
vector<vector<pi>> adj;

ll dist[3][101012];
int cs=0;

void dstra(int sx){
    priority_queue<pl> pq;
    pq.push({0,sx});
    dist[cs][sx]=0;
    while(!pq.empty()){
        ll cx, cc;
        tie(cc,cx)=pq.top();
        cc=-cc;
        pq.pop();
        if(dist[cs][cx]<cc)continue;
        for(auto p : adj[cx]){
            int nx,nc;
            tie(nx,nc)=p;
            if(dist[cs][nx]<=cc+nc)continue;
            dist[cs][nx]=cc+nc;
            pq.push({-(cc+nc),nx});
        }
    }
    cs++;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    cin >> A >> B >> C;
    cin >> M;
    adj=vector<vector<pi>>(N+1,vector<pi>());
    vector<int> v;
    vector<bool> ok(N+1);
    for(int i =0; i < N; i++){
        v.push_back(i+1);
    }
    for(int i = 0; i < M; i++){
        int a,b,c;
        cin >> a >> b >> c;
        adj[a].push_back({b,c});
        adj[b].push_back({a,c});
    }
    for(int i = 0; i < 3; i++){
        for(int j = 0; j <= N+1; j++){
            dist[i][j]=LNF;
        }
    }
    
    dstra(A);
    dstra(B);
    dstra(C);
    
    sort(v.begin(),v.end(),[&](int a, int b){
        if(dist[0][a]==dist[0][b]){
            if(dist[1][a]==dist[1][b]){
                return dist[2][a]>dist[2][b];
            }
            return dist[1][a]>dist[1][b];
        }
        return dist[0][a]<dist[0][b];
    });
    vector<ll> ylist;
    for(int cx : v){
        ylist.push_back(dist[1][cx]);
    }
    sort(ylist.begin(),ylist.end());
    ylist.erase(unique(ylist.begin(), ylist.end()), ylist.end());
    map<ll,int> idxs;
    for(int i = 1; i <= ylist.size(); i++){
        idxs[ylist[i-1]]=i+1;
    }
    
    segtree seg(ylist.size()+2);
    vector<vector<int>> asets;
    asets.push_back({v[0]});
    
    for(int i = 1; i < N; i++){
        if(dist[0][v[i]]==dist[0][v[i-1]]){
            asets.back().push_back(v[i]);
        }
        else{
            asets.push_back({v[i]});
        }
    }
   
    for(auto cv : asets){
        for(auto i : cv){
            ll res = seg.query(1,1,seg.size,1,idxs[dist[1][i]]-1);
            
            if(res<dist[2][i])ok[i]=0;
            else ok[i]=1;
        }
        for(auto i : cv){
            seg.update(idxs[dist[1][i]],dist[2][i]);
        }
    }
    
    int Q;
    cin >> Q;
    while(Q--){
        int a;
        cin >> a;
        //TODO query
        if(ok[a]){
            cout << "YES\n";
        }
        else cout << "NO\n";
        
    }
}