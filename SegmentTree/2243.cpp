#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int N, M, K;

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
	void update_range(int node, int nStart, int nEnd, int rStart, int rEnd, int diff) {
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
	ll query(ll val, int node, int nStart, int nEnd){
		update_lazy(node, nStart, nEnd);
		if(nStart==nEnd)return nStart;
		int mid = (nStart+nEnd)/2;
		if(val<=tree[node*2]){
			return query(val, node*2, nStart, mid);
		}
		else return query(val-tree[node*2], node*2+1, mid+1, nEnd);
	}
	
};

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int a, b, c;
	cin >> N;
	segtree seg(1e6+1);
    for(int i = 0; i < N; i++){
        cin >> a >> b;
        if(a==2){
            cin >> c;
            seg.update_range(1,1,seg.size,b,b,c);
        }
        else if(a==1){
            ll ans = seg.query(b,1,1,seg.size);
            cout << ans << '\n';
            seg.update_range(1,1,seg.size,ans,ans,-1);
        }
    }
}