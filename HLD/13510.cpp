#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using Edge = pair<int, pair<int,int>>;
using pi = pair<int,int>;

int N, M, cnt;
int weight[100002], depth[100002];
int parents[100002][20];
//numbers : the numbered value of a node(for decomposition)
//ori : the original index number of n[u](ori[n[u]])
//hld : the vertex with minimum depth value in the range of u(hld[u])
int numbers[100002], ori[100002], hld[100002];

vector<vector<pi>> adj;
vector<Edge> edges;

class segtree {
public:
	vector<int> tree;
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
            tree[pos >> 1] = max(tree[pos] , tree[pos ^ 1]); // update by rule
        }
    }

    //[l,r)
	int query(int l, int r) {
        r++;
        int ans = 0;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l & 1) ans = max(ans, tree[l++]);
            if (r & 1) ans = max(ans, tree[--r]);
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
    for(auto& a:adj[u]){
        int v = a.first;
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
    for(auto& a: adj[u]){
        int v = a.first;
        if(parents[v][0]==u&&(heavyidx==-1||weight[v]>weight[heavyidx]))heavyidx=v;
    }
    //if found, link the current vertex with it as the same group and continue the split
    if(heavyidx!=-1){
        hld[heavyidx]=hld[u];
        split(heavyidx);
    }
    //the remaining children are all first nodes of a new group
    for(auto& a : adj[u]){
        int v= a.first;
        if(parents[v][0]==u&&v!=heavyidx){
            hld[v]=v;
            split(v);
        }
    }
}

void update(int eidx, int x){
    if(depth[edges[eidx].second.first]>depth[edges[eidx].second.second]){
        seg.update(numbers[edges[eidx].second.first],x);
    }
    else{
        seg.update(numbers[edges[eidx].second.second],x);
    }
}
//v is ancestor of u
int hld_query(int u, int v){
    int ret=0;
    while(hld[u]!=hld[v]){
        ret=max(ret,seg.query(numbers[hld[u]],numbers[u]));
        u=parents[hld[u]][0];
    }
    if(u!=v){
        ret=max(ret,seg.query(numbers[v]+1,numbers[u]));
    }
    return ret;
}
int query(int u, int v){
    int l = lca(u,v);
    return max(hld_query(u,l),hld_query(v,l));
}
//hldend

int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N;
    seg=segtree(N);
    adj= vector<vector<pi>>(N+1,vector<pi>());
    for(int i = 0;i  < N-1; i++){
        int a,b,c;
        cin >> a >> b >> c;
        adj[a].push_back({b,c});
        adj[b].push_back({a,c});
        edges.push_back({c,{a,b}});
    }
    dfs(1);
    split(1);
    for(int i = 1;i  < 20; i++){
        for(int j = 1; j <= N; j++){
            parents[j][i]=parents[parents[j][i-1]][i-1];
        }
    }
    for(int i=0;i<N-1;i++){
        update(i,edges[i].first);
    }
    cin >> M;
    for(int i = 0; i < M; i++){
        int c;
        int u, v;
        cin >> c >> u >> v;
        if(c==1){
            edges[u-1].first=v;
            update(u-1,v);
        }
        else{
            cout << query(u,v) << '\n';
        }
    }
}