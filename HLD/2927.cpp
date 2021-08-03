#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using Edge = pair<int, pair<int,int>>;
using pi = pair<int,int>;

const int MAX_N = 30002;
int N, Q, cnt;
int weight[MAX_N], depth[MAX_N];
int parents[MAX_N][20];
//numbers : the numbered value of a node(for decomposition)
//ori : the original index number of n[u](ori[n[u]])
//hld : the vertex with minimum depth value in the range of u(hld[u])
int numbers[MAX_N], ori[MAX_N], hld[MAX_N];

vector<vector<int>> adj;

class UnionFind{
    public:
        int p[MAX_N];
    UnionFind(){
        for(int i = 0; i < MAX_N; i++){
            p[i]=i;
        }
    }
    int find(int v){
        return v == p[v]?v:p[v]=find(p[v]);
    }
    bool uni(int u, int v){
        u=find(u);v=find(v);
        if(u==v)return 0;
        p[u]=v;
        return 1;
    }
};

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
	void update(int pos, ll val) {
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
    for(auto& v : adj[u]){
        
        if(parents[v][0]==u&&v!=heavyidx){
            hld[v]=v;
            split(v);
        }
    }
}

void update(int eidx, int x){
    seg.update(numbers[eidx],x);
}
//v is ancestor of u
ll hld_query(int u, int v){
    ll ret=0;
    while(hld[u]!=hld[v]){
        if(depth[hld[u]] < depth[hld[v]])swap(u,v);
        ret+=seg.query(numbers[hld[u]],numbers[u]);
        u=parents[hld[u]][0];
    }
    if(depth[u]>depth[v])swap(u,v);
    return ret + seg.query(numbers[u],numbers[v]);
}
ll query(int u, int v){
    
    return hld_query(u,v);
}
//hldend
struct Query{
    string s; int a, b;
};
vector<Query> vq;


int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    UnionFind UF;
    seg=segtree(N);
    adj= vector<vector<int>>(N+1,vector<int>());
    vector<int> evals;
    for(int i = 0;i  < N; i++){
        int a;
        cin >> a;
        evals.push_back(a);
    }
    cin >> Q;
    //pre-process the links for hld(we will use UF to keep track of the links in query order)
    for(int i = 0; i < Q ;i++){
        string s;
        int a, b;
        cin >> s >> a >> b;
        vq.push_back({s,a,b});
        if(s[0]=='b'){
            if(UF.uni(a,b)){
                adj[a].push_back(b);
                adj[b].push_back(a);
            }
        }
    }
    //link all unlinked nodes for now for easy hld
    for(int i = 1; i <= N; i++){
        if(UF.uni(1,i)){
            adj[1].push_back(i);adj[i].push_back(1);
        }
    }
    
    dfs(1);
    split(1);
    
    for(int i=1;i<=N;i++){
        update(i,evals[i-1]);
    }
    //reset UF for query processing
    for(int i = 0; i < MAX_N; i++){
        UF.p[i]=i;
    }
    
    
    for(int i = 0; i < Q; i++){
        Query q = vq[i];
        if(q.s[0]=='b'){
            if(UF.uni(q.a,q.b))cout << "yes\n";
            else cout << "no\n";
        }
        else if(q.s[0]=='p'){
            update(q.a,q.b);
        }
        else{
            if(UF.find(q.a)!=UF.find(q.b))cout << "impossible\n";
            else cout << query(q.a,q.b) << '\n';
        }
    }
}