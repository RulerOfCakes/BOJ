#include <bits/stdc++.h>

using namespace std;
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
	long long getmax(int node, int nStart, int nEnd, int rStart, int rEnd){
		update_lazy(node, nStart, nEnd);
		if(nEnd < rStart || nStart > rEnd) return 0;
		if(rStart <= nStart && nEnd > rEnd) return tree[node];
		int mid = (nStart + nEnd) / 2;
		return max(getmax(node*2, nStart, mid, rStart, rEnd), getmax(node*2+1, mid+1, nEnd, rStart, rEnd));
	}
	long long lazies(int node) {
		int idx = node + size - 1;
		long long ans = 0;
		while (idx) {
			ans += lazy[idx];
			idx /= 2;
		}
		return ans + tree[node + size - 1];
	}
	
};

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int a, b, c;
	cin >> N;
	segtree seg(N);
	for (int n = 0; n < N; n++) {
		cin >> a;
		seg.update(n+1, a);
	}
	cin >> M;
	for (int i = 0; i < M; i ++ ) {
		cin >> a;
		if (a == 1) {
			cin >> b >> c;
			seg.update(b, c);
		}
		if (a == 2) {
			cin >> b >> c;
			cout << seg.getmax(1, 1, seg.size, b, c) << "\n";
		}
	}
}