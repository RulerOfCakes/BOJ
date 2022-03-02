#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int N,C,Q;
vector<int> adj[202020];
int l[202020],r[202020];
int depth[202020];

class segtree{

    public:
    vector<ll> tree;
    int size;
    segtree(int n){
        for(size=1;size<=2*n;size*=2);
        tree.resize(size*2);
    }
    void update(int pos, ll x){
        int idx = pos+size-1;
        while(idx){
            tree[idx]+=x;
            idx>>=1;
        }
    }
    ll getsum(int node, int nStart, int nEnd, int rStart, int rEnd) {
		if (nEnd < rStart || nStart > rEnd) return 0;
		if (rStart <= nStart && rEnd >= nEnd) return tree[node];
		int mid = (nStart + nEnd) / 2;
		return getsum(node * 2, nStart, mid, rStart, rEnd) + getsum(node * 2 + 1, mid+1, nEnd, rStart, rEnd);
	}
};

int cnt=0;
void dfs(int cx, int prt){
    l[cx]=++cnt;
    depth[cx]=depth[prt]+1;
    for(int nx : adj[cx]){
        if(nx==prt)continue;
        dfs(nx,cx);
    }
    r[cx]=cnt;
}
int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin>>N>>C;
    for(int i = 0; i < N-1; i++){
        int a,b;
        cin>>a>>b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(C, 0);
    segtree cseg(N+1);
    cin>>Q;
    while(Q--){
        int a,b;
        cin>>a>>b;
        if(a==1){
            cseg.update(l[b],1);
        } else {
            cout << cseg.getsum(1,1,cseg.size,l[b],r[b])*depth[b] << '\n';
        }
    }
}