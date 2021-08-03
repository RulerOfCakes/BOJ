#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using Edge = pair<int, pair<int,int>>;
using pi = pair<int,int>;

int N, M, cnt;
const int MAX_N=250002;
int weight[MAX_N], depth[MAX_N];
int parents[MAX_N][20];
//numbers : the numbered value of a node(for decomposition)
//ori : the original index number of n[u](ori[n[u]])
//hld : the vertex with minimum depth value in the range of u(hld[u])
int numbers[MAX_N], ori[MAX_N], hld[MAX_N];

vector<vector<int>> adj;
vector<Edge> edges;

class segtree {
public:
	vector<ll> tree;
	//vector<long long> cnt; // count of lines
	//vector<long long> sum; // sum of squares
	//vector<long long> lazy; // lazy propagataion
	int size;

	segtree (int n) {
		for (size = 1; size < n; size *= 2);
		tree.resize(size * 2, 0);
		//lazy.resize(size * 2);
		//cnt.resize(size * 2);
		//sum.resize(size * 2);
	}
	void update(int pos, int val) {
        tree[pos + N] = val; // update
        for (pos += N; pos > 1; pos >>= 1) {
            tree[pos >> 1] = tree[pos] + tree[pos ^ 1]; // update by rule
        }
    }

    //[l,r)
	ll query(int l, int r) {
        r++;
        ll ans = 0;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ans += tree[l++];
            if (r & 1) ans += tree[--r];
        }
        return ans;
    }
	
};
segtree seg(1);

//lca
int lca(int u, int v){
    if(depth[u]>depth[v])swap(u,v);
    //dragging v up to the same depth as u
    for(int i = 19; i >=0; i--){
        if(depth[v]-depth[u]>=(1<<i))v=parents[v][i];
    }
    if(u==v)return u;
    //dragging both as far up as possible
    for(int i = 19; i >=0; i--){
        if(parents[u][i]!=parents[v][i]){
            u=parents[u][i];
            v=parents[v][i];
        }
    }
    return parents[u][0];
}
//lca end
//hld
void dfs(int u){
    weight[u]=1;
    for(auto& v:adj[u]){
        
        if(!weight[v]){
            
            parents[v][0]=u;
            depth[v]=depth[u]+1;
            dfs(v);
            weight[u]+=weight[v];
        }
    }
}

void split(int u){
    int heavyidx=-1;
    numbers[u] = ++cnt;
    ori[numbers[u]]=u;
    //find the heaviest child
    for(auto& v: adj[u]){
        
        if(parents[v][0]==u&&(heavyidx==-1||weight[v]>weight[heavyidx]))heavyidx=v;
    }
    //if found, link the current vertex with it as the same group and continue the split
    if(heavyidx!=-1){
        hld[heavyidx]=hld[u];
        split(heavyidx);
    }
    //the remaining children are all first nodes of a new group
    for(auto& v: adj[u]){
        
        if(parents[v][0]==u&&v!=heavyidx){
            hld[v]=v;
            split(v);
        }
    }
}

void update(int u, int v, int x){
    if(depth[u]>depth[v]){
        seg.update(numbers[u],x);
    }
    else{
        seg.update(numbers[v],x);
    }
}
//v is ancestor of u
ll hld_query(int u, int v){
    ll ret=0;
    while(hld[u]!=hld[v]){
        ret+=seg.query(numbers[hld[u]],numbers[u]);
        u=parents[hld[u]][0];
    }
    if(u!=v){
        ret+=seg.query(numbers[v]+1,numbers[u]);
    }
    return ret;
}
ll query(int u, int v){
    int l = lca(u,v);
    return hld_query(u,l)+hld_query(v,l);
}
//hldend

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    seg=segtree(N);
    adj= vector<vector<int>>(N+1,vector<int>());
    for(int i = 0;i  < N-1; i++){
        int a,b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
        edges.push_back({1,{a,b}});
    }
    dfs(1);
    split(1);
    for(int i = 1;i  < 20; i++){
        for(int j = 1; j <= N; j++){
            parents[j][i]=parents[parents[j][i-1]][i-1];
        }
    }
    for(int i=0;i<N-1;i++){
        update(edges[i].second.first,edges[i].second.second,edges[i].first);
    }
    cin >> M;
    for(int i = 1; i < N+M; i++){
        char c;
        int u, v;
        cin >> c >> u;
        if(c=='A'){
            cin >> v;
            update(u,v,0);
        }
        else{
            cout << query(1,u) << '\n';
        }
    }
}