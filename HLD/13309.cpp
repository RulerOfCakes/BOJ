#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int N, M, cnt;
int weight[202020], depth[202020];
int parents[202020][20];
//numbers : the numbered value of a node(for decomposition)
//ori : the original index number of n[u](ori[n[u]])
//hld : the vertex with minimum depth value in the range of u(hld[u])
int numbers[202020], ori[202020], hld[202020];

vector<vector<int>> adj;

class segtree {
public:
	vector<long long> tree;
	//vector<long long> cnt; // count of lines
	//vector<long long> sum; // sum of squares
	vector<long long> lazy; // lazy propagataion
	int size;

	segtree (int n) {
		for (size = 1; size < n; size *= 2);
		tree.resize(size * 2, 0);
		lazy.resize(size * 2);
		//cnt.resize(size * 2);
		//sum.resize(size * 2);
	}
	void update(int node, long long x) {
		int idx = size + node - 1;
		long long diff = x - tree[idx];
		while (idx) {
			tree[idx] += diff;
			idx /= 2;
		}
	}
	void update_lazy(int node, int start, int end) {
		if (!lazy[node])return;
		tree[node] += lazy[node] * (end - start + 1);
		if (start != end) {
			lazy[node * 2] += lazy[node];
			lazy[node * 2 + 1] += lazy[node];
		}
		lazy[node] = 0;
	}
	void update_range(int node, int nStart, int nEnd, int rStart, int rEnd, ll diff) {
		update_lazy(node, nStart, nEnd);
		if (nEnd < rStart || nStart > rEnd)return;
		if (nStart >= rStart && nEnd <= rEnd) {
			lazy[node] = diff;
			update_lazy(node, nStart, nEnd);
			return;
		}
		
		int mid = (nStart + nEnd) / 2;
		update_range(node*2, nStart, mid, rStart, rEnd, diff);
		update_range(node*2+1, mid + 1, nEnd, rStart, rEnd, diff);
		tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}
	long long getsum(int node, int nStart, int nEnd, int rStart, int rEnd) {
		update_lazy(node, nStart, nEnd);
		if (nEnd < rStart || nStart > rEnd) return 0;
		if (rStart <= nStart && rEnd >= nEnd) return tree[node];
		int mid = (nStart + nEnd) / 2;
		return getsum(node * 2, nStart, mid, rStart, rEnd) + getsum(node * 2 + 1, mid+1, nEnd, rStart, rEnd);
	}
	// ll query(ll val, int node, int nStart, int nEnd){
	// 	update_lazy(node, nStart, nEnd);
	// 	if(nStart==nEnd)return nStart;
	// 	int mid = (nStart+nEnd)/2;
	// 	if(val<=tree[node*2]){
	// 		return query(val, node*2, nStart, mid);
	// 	}
	// 	else return query(val-tree[node*2], node*2+1, mid+1, nEnd);
	// }
	
};

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

void update(int u, int v, ll val, segtree& seg){
    while(hld[u]!=hld[v]){
        //u is the deeper node
        if(depth[hld[u]] < depth[hld[v]])swap(u,v);
        seg.update_range(1,1,seg.size,numbers[hld[u]],numbers[u],val);
        u=parents[hld[u]][0];
    }
    if(depth[u]>depth[v])swap(u,v);
    if(u==v)return;
    seg.update_range(1,1,seg.size,numbers[u]+1,numbers[v],val);
}

ll getsum(int u, int v, segtree& seg){
    ll ret=0;
    while(hld[u]!=hld[v]){
        if(depth[hld[u]]<depth[hld[v]])swap(u,v);
        ret+=seg.getsum(1,1,seg.size,numbers[hld[u]],numbers[u]);
        u=parents[hld[u]][0];
    }
    if(depth[u]>depth[v])swap(u,v);
    if(u==v)return ret;
    return ret+seg.getsum(1,1,seg.size,numbers[u]+1,numbers[v]);
}
ll query(int u, int v, segtree& seg){
    int l = lca(u,v);
    return getsum(u,l, seg)+getsum(v,l, seg);
}
void update_query(int u, int v, ll val, segtree& seg){
    int l = lca(u,v);
    update(u,l,val,seg);
    update(v,l,val,seg);
}
int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M;
    segtree seg(N);
    adj= vector<vector<int>>(N+1,vector<int>());
    for(int i = 1;i  <= N-1; i++){
        int a,b;
        cin >> a;
        adj[a].push_back(i+1);
        adj[i+1].push_back(a);
    }
    dfs(1);
    split(1);
    for(int i = 1;i  < 20; i++){
        for(int j = 1; j <= N; j++){
            parents[j][i]=parents[parents[j][i-1]][i-1];
        }
    }
    for(int i = 0; i < M; i++){
        int d;
        int u, v;
        cin >> u >> v >> d;
        if(d==0){
            int res=query(u,v,seg);
            if(res){
                cout << "NO\n";
            }
            else cout << "YES\n";
        }
        else{
            
            int res=query(u,v,seg);
            if(res){
                if(parents[v][0]!=0)
                update_query(v,parents[v][0],1,seg);

                cout << "NO\n";
            }
            else{
                if(parents[u][0]!=0)
                update_query(u,parents[u][0],1,seg);
                
                cout << "YES\n";
            }
        }
    }
}